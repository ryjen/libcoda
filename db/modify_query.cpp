#include "modify_query.h"
#include "database_exception.h"
#include "../collections/collections.h"
#include "../strings/strings.h"

namespace arg3
{
	namespace db
	{

        modify_query::modify_query(const base_record &record) : base_query(record.db(), record.tableName(), record.columns()) {
        }

        modify_query::modify_query(const sqldb &db, const string &tableName, 
        	const column_definition &columns) : base_query(db, tableName, columns)
        {}

        modify_query::modify_query(const sqldb &db, const string &tableName) : base_query(db, tableName)
        {}

        string modify_query::to_string() const
        {
            ostringstream buf;

            buf << "REPLACE INTO " << m_tableName;

            if (m_columns.size() > 0)
            {
                buf << "(";

                buf << join(m_columns);

                buf << ") VALUES (";

                buf << join('?', m_columns.size());

                buf << ")";
            }
            else
            {
                buf << " DEFAULT VALUES";
            }

            return buf.str();
        }

        bool modify_query::execute(bool batch)
        {
        	prepare();

            int res = sqlite3_step(m_stmt);

            if(!batch) {
                if(sqlite3_finalize(m_stmt) != SQLITE_OK)
                    throw database_exception();

                m_stmt = NULL;
            }
            else {
                if(sqlite3_reset(m_stmt) != SQLITE_OK)
                    throw database_exception();
            }

            return res == SQLITE_DONE;
        }
	}
}