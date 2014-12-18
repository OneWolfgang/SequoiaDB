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

   Source File Name = rtnSQLMin.cpp

   Descriptive Name =

   When/how to use: this program may be used on binary and text-formatted
   versions of PMD component. This file contains declare for QGM operators

   Dependencies: N/A

   Restrictions: N/A

   Change Activity:
   defect Date        Who Description
   ====== =========== === ==============================================
          04/09/2013  YW  Initial Draft

   Last Changed =

*******************************************************************************/

#include "rtnSQLMin.hpp"

namespace engine
{
   _rtnSQLMin::_rtnSQLMin()
   {
      _name = "min" ;
   }

   _rtnSQLMin::~_rtnSQLMin()
   {

   }

   INT32 _rtnSQLMin::result( BSONObjBuilder &builder )
   {
      INT32 rc = SDB_OK ;

      try
      {
         if ( _ele.eoo() )
         {
            builder.appendNull( _alias.toString() ) ;
         }
         else
         {
            builder.appendAs( _ele, _alias.toString() ) ;
         }

         _obj = BSONObj() ;
         _ele = BSONElement() ;
      }
      catch ( std::exception &e )
      {
         PD_LOG( PDERROR, "unexcepted err happened:%s",
                 e.what() ) ;
         rc = SDB_SYS ;
         goto error ;
      }

   done:
      return rc ;
   error:
      goto done ;
   }

   INT32 _rtnSQLMin::_push( const RTN_FUNC_PARAMS &param )
   {
      INT32 rc = SDB_OK ;
      try
      {
         const BSONElement &ele = *(param.begin()) ;
         if ( ele.eoo() || ele.isNull() )
         {
            goto done ;
         }
         else if ( _ele.eoo() )
         {
            BSONObjBuilder builder ;
            builder.append( ele ) ;
            _obj = builder.obj() ;
            _ele = _obj.firstElement() ;
         }
         else if ( 0 < _ele.woCompare( ele, FALSE ) )
         {
            BSONObjBuilder builder ;
            builder.append( ele ) ;
            _obj = builder.obj() ;
            _ele = _obj.firstElement() ;
         }
         else
         {
         }
      }
      catch ( std::exception &e )
      {
         PD_LOG( PDERROR, "unexcepted err happened:%s",
                 e.what() ) ;
         rc = SDB_SYS ;
         goto error ;
      }
   done:
      return rc ;
   error:
      goto done ;
   }
}
