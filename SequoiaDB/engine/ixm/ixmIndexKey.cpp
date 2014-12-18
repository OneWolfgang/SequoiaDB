/*******************************************************************************


   Copyright (C) 2011-2014 SequoiaDB Ltd.

   This program is free software: you can redistribute it and/or modify
   it under the term of the GNU Affero General Public License, version 3,
   as published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warrenty of
   MARCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU Affero General Public License for more details.

   You should have received a copy of the GNU Affero General Public License
   along with this program. If not, see <http://www.gnu.org/license/>.

   Source File Name = ixmIndexKey.cpp

   Descriptive Name = Index Manager Index Key Generator

   When/how to use: this program may be used on binary and text-formatted
   versions of Index Manager component. This file contains functions for index
   key generator, which is used to create key pairs from data record and index
   definition.

   Dependencies: N/A

   Restrictions: N/A

   Change Activity:
   defect Date        Who Description
   ====== =========== === ==============================================
          09/14/2012  TW  Initial Draft

   Last Changed =

*******************************************************************************/
#include "ixm.hpp"
#include "ixmIndexKey.hpp"
#include "ossMem.hpp"
#include "pdTrace.hpp"
#include "ixmTrace.hpp"

using namespace bson ;

namespace engine
{

   #define IXM_MAX_PREALLOCATED_UNDEFKEY        ( 10 )
   /*
      IXM Tool functions
   */
   BSONObj ixmGetUndefineKeyObj( INT32 fieldNum )
   {
      static BSONObj s_undefineKeys[ IXM_MAX_PREALLOCATED_UNDEFKEY ] ;
      static BOOLEAN s_init = FALSE ;
      static ossSpinXLatch s_latch ;

      if ( FALSE == s_init )
      {
         s_latch.get() ;
         if ( FALSE == s_init )
         {
            for ( SINT32 i = 0; i < IXM_MAX_PREALLOCATED_UNDEFKEY ; ++i )
            {
               BSONObjBuilder b ;
               for ( SINT32 j = 0; j <= i; ++j )
               {
                  b.appendUndefined("") ;
               }
               s_undefineKeys[i] = b.obj() ;
            }
            s_init = TRUE ;
         }
         s_latch.release() ;
      }

      if ( fieldNum > 0 && fieldNum <= IXM_MAX_PREALLOCATED_UNDEFKEY )
      {
         return s_undefineKeys[ fieldNum - 1 ] ;
      }
      else
      {
         BSONObjBuilder b ;
         for ( INT32 i = 0; i < fieldNum; ++i )
         {
            b.appendUndefined("") ;
         }
         return b.obj() ;
      }
   }

   /*
      IXM Global opt var
   */
   const static BSONObj gUndefinedObj =
          BSONObjBuilder().appendUndefined("").obj() ;
   const static BSONElement gUndefinedElt = gUndefinedObj.firstElement() ;

   class _ixmKeyGenerator
   {
   protected:
      const _ixmIndexKeyGen *_keygen ;
      mutable vector<BSONObj *> _objs ;
   public:
      _ixmKeyGenerator ( const _ixmIndexKeyGen *keygen )
      {
         _keygen = keygen ;
      }
      ~_ixmKeyGenerator()
      {
         vector<BSONObj *>::iterator itr = _objs.begin() ;
         for ( ; itr != _objs.end(); itr++ )
         {
            SDB_OSS_DEL *itr ;
         }
      }
      // PD_TRACE_DECLARE_FUNCTION ( SDB__IXMKEYGEN_GETKEYS, "_ixmKeyGenerator::getKeys" )
      INT32 getKeys ( const BSONObj &obj, BSONObjSet &keys,
                      BSONElement *pArrEle ) const
      {
         INT32 rc = SDB_OK ;
         PD_TRACE_ENTRY ( SDB__IXMKEYGEN_GETKEYS );
         SDB_ASSERT( _keygen, "spec can't be NULL" ) ;
         SDB_ASSERT( !_keygen->_fieldNames.empty(), "can not be empty" ) ;
         vector<const CHAR*> fieldNames ( _keygen->_fieldNames ) ;
         BSONElement arrEle ;
         try
         {
            rc = _getKeys( fieldNames, obj, keys, &arrEle ) ;
         }
         catch ( std::exception &e )
         {
            PD_LOG( PDERROR, "unexpected err:%s", e.what() ) ;
            rc = SDB_INVALIDARG ;
            goto error ;
         }

         if ( SDB_OK != rc )
         {
            PD_LOG ( PDERROR, "Failed to generate key from object: %s",
                     obj.toString().c_str() ) ;
            goto error ;
         }

         if ( keys.empty() )
         {
            keys.insert ( _keygen->_undefinedKey ) ;
         }

         if ( NULL != pArrEle && !arrEle.eoo() )
         {
            *pArrEle = arrEle ;
         }
      done :
         PD_TRACE_EXITRC ( SDB__IXMKEYGEN_GETKEYS, rc );
         return rc ;
      error :
         goto done ;
      }
   protected:
      // PD_TRACE_DECLARE_FUNCTION ( SDB__IXMKEYGEN__GETKEYS, "_ixmKeyGenerator::_getKeys" )
      INT32 _getKeys( vector<const CHAR *> &fieldNames,
                      const BSONObj &obj,
                      BSONObjSet &keys,
                      BSONElement *arrEle ) const
      {
         INT32 rc = SDB_OK ;
         PD_TRACE_ENTRY ( SDB__IXMKEYGEN__GETKEYS );
#define IXM_DEFAULT_FIELD_NUM 3
         BSONElement eleOnStack[IXM_DEFAULT_FIELD_NUM] ;
         BSONElement *keyEles = NULL ;
         const CHAR *arrEleName = NULL ;
         UINT32 arrElePos = 0 ;
         UINT32 eooNum = 0 ;

         if ( IXM_DEFAULT_FIELD_NUM < fieldNames.size() )
         {
            keyEles = new(std::nothrow) BSONElement[fieldNames.size()] ;
            if ( NULL == keyEles )
            {
               PD_LOG( PDERROR, "failed to allocalte mem." ) ;
               rc = SDB_OOM ;
               goto error ;
            }
         }
         else
         {
            keyEles = ( BSONElement* )eleOnStack ;
         }

         for ( UINT32 i = 0; i < fieldNames.size(); i++ )
         {
            const CHAR *name = fieldNames.at( i ) ;
            SDB_ASSERT( '\0' != name[0], "can not be empty" ) ;
            BSONElement &e = keyEles[i] ;
            e = obj.getFieldDottedOrArray( name ) ;
            if ( e.eoo() )
            {
               ++eooNum ;
               continue ;
            }
            else if ( Array == e.type() )
            {
               if ( !arrEle->eoo() )
               {
                  PD_LOG( PDERROR, "At most one array can be in the key:",
                          arrEle->fieldName(), e.fieldName() ) ;
                  rc = SDB_IXM_MULTIPLE_ARRAY ;
                  goto error ;
               }
               else
               {
                  *arrEle = e ;
                  arrEleName = name ;
                  arrElePos = i ;
               }
            }
            else
            {
               continue ;
            }
         }

         if ( fieldNames.size() == eooNum )
         {
            rc = SDB_OK ;
            goto done ;
         }
         else if ( !arrEle->eoo() )
         {
            rc = _genKeyWithArrayEle( keyEles, fieldNames.size(),
                                      arrEle->embeddedObject(),
                                      arrEleName, arrElePos,
                                      keys ) ;
            if ( SDB_OK != rc )
            {
               PD_LOG( PDERROR, "failed to gen keys with array element:%d", rc ) ;
               goto error ;
            }
         }
         else
         {
            rc = _genKeyWithNormalEle( keyEles, fieldNames.size(), keys ) ;
            if ( SDB_OK != rc )
            {
               PD_LOG( PDERROR, "failed to gen keys with normal element:%d", rc ) ;
               goto error ;
            }
         }
      done:
         if ( IXM_DEFAULT_FIELD_NUM < fieldNames.size() &&
              NULL != keyEles )
         {
            delete []keyEles ;
         }
         PD_TRACE_EXITRC ( SDB__IXMKEYGEN__GETKEYS, rc );
         return rc ;
      error:
         goto done ;
      }

      // PD_TRACE_DECLARE_FUNCTION ( SDB__IXMKEYGEN__GENKEYSWITHARRELE, "_ixmKeyGenerator::_genKeyWithArrayEle" )
      INT32 _genKeyWithArrayEle( BSONElement *keyEles,
                                 UINT32 eleNum,
                                 const BSONObj &arrObj,
                                 const CHAR *arrEleName,
                                 UINT32 arrElePos,
                                 BSONObjSet &keys ) const
      {
         PD_TRACE_ENTRY ( SDB__IXMKEYGEN__GENKEYSWITHARRELE );
         INT32 rc = SDB_OK ;

         if ( arrObj.firstElement().eoo() )
         {
            keyEles[arrElePos] = BSONElement() ;
            rc = _genKeyWithNormalEle( keyEles, eleNum, keys ) ;
            if ( SDB_OK != rc )
            {
               goto error ;
            }
         }

         if ( '\0' == *arrEleName )
         {
            BSONObjIterator itr( arrObj ) ;
            BSONElement &e = keyEles[arrElePos] ;
            while ( itr.more() )
            {
               e = itr.next() ;
               rc = _genKeyWithNormalEle( keyEles, eleNum, keys ) ;
               if ( SDB_OK != rc )
               {
                  goto error ;
               }
            }
         }
         else
         {
            BSONObjIterator itr( arrObj ) ;
            while ( itr.more() )
            {
               const CHAR *dottedName = arrEleName ;
               BSONElement next = itr.next() ;
               if ( Object == next.type() )
               {
                  BSONElement e =
                     next.embeddedObject()
                     .getFieldDottedOrArray( dottedName ) ;
                  if ( Array == e.type() )
                  {
                     rc = _genKeyWithArrayEle(keyEles, eleNum,
                                              e.embeddedObject(),
                                              dottedName, arrElePos,
                                              keys) ;
                     if ( SDB_OK != rc )
                     {
                        goto error ;
                     }
                     else
                     {
                        continue ;
                     }
                  }
                  else
                  {
                     keyEles[arrElePos] = e ;
                  }
               }
               else
               {
                  keyEles[arrElePos] = BSONElement() ;
               }

               rc = _genKeyWithNormalEle( keyEles, eleNum, keys ) ;
               if ( SDB_OK != rc )
               {
                  goto error ;
               }
            } 
         }
      done:
         PD_TRACE_EXITRC( SDB__IXMKEYGEN__GENKEYSWITHARRELE, rc ) ;
         return rc ;
      error:
         goto done ;
      }

      // PD_TRACE_DECLARE_FUNCTION ( SDB__IXMKEYGEN__GENKEYSWITHNORMALELE, "_ixmKeyGenerator::_genKeyWithNormalEle" )
      INT32 _genKeyWithNormalEle( BSONElement *keyELes,
                                  UINT32 eleNum,
                                  BSONObjSet &keys ) const
      {
         PD_TRACE_ENTRY ( SDB__IXMKEYGEN__GENKEYSWITHNORMALELE );
         INT32 rc = SDB_OK ;
         BSONObjBuilder builder ;
         for ( UINT32 i = 0; i < eleNum; i++ )
         {
            BSONElement &e = keyELes[i] ;
            if ( e.eoo() )
            {
               builder.appendAs( gUndefinedElt, "" ) ;
            }
            else
            {
               builder.appendAs( e, "" ) ;
            }
         }

         keys.insert( builder.obj() ) ;
         PD_TRACE_EXITRC ( SDB__IXMKEYGEN__GENKEYSWITHNORMALELE, rc );
         return rc ;
      }
   } ;
   typedef class _ixmKeyGenerator ixmKeyGenerator ;
   _ixmIndexKeyGen::_ixmIndexKeyGen ( const _ixmIndexCB *indexCB,
                                      IXM_KEYGEN_TYPE genType )
   {
      SDB_ASSERT ( indexCB, "details can't be NULL" ) ;
      _keyPattern = indexCB->keyPattern() ;
      _info = indexCB->_infoObj ;
      _type = indexCB->getIndexType() ;
      _keyGenType = genType ;
      _init() ;
   }
   _ixmIndexKeyGen::_ixmIndexKeyGen ( const BSONObj &keyDef,
                                      IXM_KEYGEN_TYPE genType )
   {
      _keyPattern = keyDef.copy () ;
      _type = IXM_EXTENT_TYPE_NONE ;
      _keyGenType = genType ;
      _init () ;
   }

   // PD_TRACE_DECLARE_FUNCTION ( SDB__IXMINXKEYGEN__INIT, "_ixmIndexKeyGen::_init" )
   void _ixmIndexKeyGen::_init()
   {
      PD_TRACE_ENTRY ( SDB__IXMINXKEYGEN__INIT );
      _nFields = _keyPattern.nFields () ;
      INT32 fieldNum = 0 ;
      {
         BSONObjIterator i(_keyPattern) ;
         while ( i.more())
         {
            BSONElement e = i.next() ;
            _fieldNames.push_back(e.fieldName()) ;
            _fixedElements.push_back(BSONElement()) ;
            ++fieldNum ;
         }
         _undefinedKey = ixmGetUndefineKeyObj( fieldNum ) ;
      }
      PD_TRACE_EXIT ( SDB__IXMINXKEYGEN__INIT );
   }

   INT32 _ixmIndexKeyGen::getKeys ( const BSONObj &obj, BSONObjSet &keys,
                                    BSONElement *pArrEle ) const
   {
      ixmKeyGenerator g (this) ;
      if ( pArrEle )
      {
         *pArrEle = BSONElement() ;
      }
      return g.getKeys ( obj, keys, pArrEle ) ;
   }

   static BOOLEAN anyElementNamesMatch( const BSONObj& a , const BSONObj& b )
   {
      BSONObjIterator x(a);
      while ( x.more() )
      {
         BSONElement e = x.next();
         BSONObjIterator y(b);
         while ( y.more() )
         {
            BSONElement f = y.next();
            FieldCompareResult res = compareDottedFieldNames( e.fieldName(),
                                                              f.fieldName()
                                                            ) ;
            if ( res == SAME || res == LEFT_SUBFIELD || res == RIGHT_SUBFIELD )
               return TRUE;
         }
      }
      return FALSE;
   }
   IndexSuitability ixmIndexKeyGen::suitability( const BSONObj &query ,
                                                 const BSONObj &order ) const
   {
      return _suitability( query , order );
   }

   IndexSuitability ixmIndexKeyGen::_suitability( const BSONObj& query ,
                                                  const BSONObj& order ) const
   {
       if ( anyElementNamesMatch( _keyPattern , query ) == 0 &&
            anyElementNamesMatch( _keyPattern , order ) == 0 )
          return USELESS;
       return HELPFUL;
   }
   
   // PD_TRACE_DECLARE_FUNCTION ( SDB_IXMINXKEYGEN, "ixmIndexKeyGen::reset" )
   INT32 ixmIndexKeyGen::reset ( const BSONObj & info )
   {
      INT32 rc = SDB_OK ;
      PD_TRACE_ENTRY ( SDB_IXMINXKEYGEN );
      _info = info ;
      try
      {
         _keyPattern = _info[IXM_KEY_FIELD].embeddedObjectUserCheck() ;
      }
      catch ( std::exception &e )
      {
         PD_LOG ( PDERROR, "Unable to locate valid key in index: %s",
                  e.what() ) ;
         rc = SDB_INVALIDARG ;
         goto error ;
      }
      if ( _keyPattern.objsize() == 0 )
      {
         PD_LOG ( PDERROR, "Empty key" ) ;
         rc = SDB_INVALIDARG ;
         goto error ;
      }
      _init() ;
   done :
      PD_TRACE_EXITRC ( SDB_IXMINXKEYGEN, rc );
      return rc ;
   error :
      goto done ;
   }
   INT32 ixmIndexKeyGen::reset ( const _ixmIndexCB *indexCB )
   {
      SDB_ASSERT ( indexCB, "details can't be NULL" ) ;
      return reset ( indexCB->_infoObj ) ;
   }
   BSONElement ixmIndexKeyGen::missingField() const
   {
      return gUndefinedElt ;
   }

   BOOLEAN _ixmIndexKeyGen::validateKeyDef ( const BSONObj &keyDef )
   {
      BSONObjIterator i ( keyDef ) ;
      INT32 count = 0 ;
      while ( i.more () )
      {
         ++count ;
         BSONElement ie = i.next () ;
         if ( ie.type() != NumberInt ||
              ( ie.numberInt() != -1 &&
                ie.numberInt() != 1 ) )
         {
            return FALSE ;
         }
      }
      return 0 != count ;
   }
}
