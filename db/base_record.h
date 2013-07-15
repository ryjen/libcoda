/*!
 * implementation of a database record
 * @copyright ryan jennings (arg3.com), 2013 under LGPL
 */
#ifndef _ARG3_DB_BASE_RECORD_H_
#define _ARG3_DB_BASE_RECORD_H_

#include "sqldb.h"
#include "select_query.h"
#include "modify_query.h"
#include "../variant/variant.h"
#include "../format/format.h"
#include "schema.h"
#include <map>
#include <memory>

namespace arg3
{
    namespace db
    {
        class sqldb;
        class row;

        template<typename T>
        class base_record
        {
        private:
            static map<string,shared_ptr<schema>> schema_cache_;

            sqldb *db_;
            string tableName_;
            shared_ptr<schema> schema_;
            map<string, variant> values_;

            void init_schema(sqldb *db, const string &tableName)
            {
                if(schema_cache_.count(tableName))
                {
                    schema_ = schema_cache_[tableName];
                }
                else
                {
                    schema_cache_[tableName] = schema_ = make_shared<db::schema>(db, tableName);
                }
            }
        public:
            /*!
             * default constructor
             */
            base_record(sqldb *db, const string &tableName) : db_(db), tableName_(tableName)
            {
                init_schema(db, tableName);
            }

            /*!
             * construct with values from a database row
             */
            base_record(sqldb *db, const string &tableName, const row &values) : db_(db), tableName_(tableName)
            {
                init_schema(db, tableName);
                init(values);
            }

            base_record(const base_record &other) :  db_(other.db_), tableName_(other.tableName_),
                values_(other.values_), schema_(other.schema_)
            {}

            base_record(base_record &&other) : db_(std::move(other.db_)), tableName_(std::move(other.tableName_)),
                values_(std::move(other.values_)), schema_(std::move(other.schema_))
            {}

            virtual ~base_record()
            {

            }

            base_record& operator=(const base_record &other)
            {
                if(this != &other)
                {
                    db_ = other.db_;
                    tableName_ = other.tableName_;
                    values_ = other.values_;
                    schema_ = other.schema_;
                }
                return *this;
            }

            base_record& operator=(base_record &&other)
            {
                if(this != &other)
                {
                    db_ = std::move(other.db_);
                    tableName_ = std::move(other.tableName_);
                    values_ = std::move(other.values_);
                    schema_ = std::move(other.schema_);
                }
                return *this;
            }

            /*!
             * initializes with values from a database row
             */
            void init(const row &values)
            {
                for (auto v = values.begin(); v != values.end(); v++)
                {
                    set(v.name(), v->to_var());
                }
            }

            bool is_valid() const
            {
                return schema_->is_valid();
            }

            /*!
             * sub classes should define the table schema here
             */
            //virtual column_definition columns() const = 0;

            /*!
             * should return the database for the record
             */
            virtual sqldb *db() const {
                return db_;
            }

            /*!
             * should return the table name for the record
             */
            string tableName() const {
                return tableName_;
            }

            const schema &schema() const
            {
                return *schema_;
            }

            /*!
             * saves this instance
             */
            bool save()
            {
                modify_query query(db(), tableName(), schema().column_names());

                int index = 1;

                // bind the object values
                for (auto & column : schema().columns())
                {
                    auto value = values_[column.name()];

                    // do an explicit null check
                    if(value.is_null())
                    {
                        query.bind(index);
                    }
                    else
                    {
                        switch (column.type())
                        {
                        case SQLITE_TEXT:
                            query.bind(index, value.to_string());
                            break;
                        case SQLITE_INTEGER:
                            query.bind(index, value.to_llong());
                            break;
                        case SQLITE_FLOAT:
                            query.bind(index, value.to_double());
                            break;
                        case SQLITE_BLOB:
                            query.bind(index, value.to_pointer(), value.size());
                        default:
                            query.bind(index);
                            break;
                        }
                    }

                    index++;
                }

                return query.execute();
            }

            /*!
             * gets a value specified by column name
             */
            variant get(const string &name) const
            {
                if(!has(name))
                    return variant();

                return values_.at(name);
            }

            /*!
             * check for the existance of a column by name
             */
            bool has(const string &name) const
            {
                return values_.count(name) > 0;
            }

            /*!
             * sets a string for a column name
             */
            virtual void set(const string &name, const variant &value)
            {
                values_[name] = value;
            }

            /*!
             * unsets / removes a column
             */
            void unset(const string &name)
            {
                values_.erase(name);
            }

            /*!
             * looks up and returns all objects of a base_record type
             */

            vector<shared_ptr<T>> findAll()
            {
                auto query = select_query(db(), tableName(), schema().column_names());

                auto results = query.execute();

                vector<shared_ptr<T>> items;

                for (auto & row : results)
                {
                    items.push_back(make_shared<T>(row));
                }

                return items;
            }

            bool refresh()
            {
                auto query = select_query(db(), tableName(), schema().column_names());

                auto params = where_clause();

                // find by primary keys
                for (auto & pk : schema().primary_keys())
                {
                    params && (format("{0} = ?", pk));
                }

                query.where(params);

                int index = 1;

                // bind primary key values
                for (auto & c : schema().columns())
                {
                    if(!c.pk()) continue;

                    query.bind(index, c.type(), values_[c.name()]);
                    index++;
                }

                auto results = query.execute();

                auto it = results.begin();

                if (it != results.end()) {
                    init(*it);
                    return  true;
                }

                return false;
            }

            template<typename V>
            vector<shared_ptr<T>> findBy(const string &name, const V &value)
            {
                auto query = select_query(db(), tableName(), schema().column_names());

                query.where(format("{0} = ?", name).str());

                query.bind(1, value);

                auto results = query.execute();

                vector<shared_ptr<T>> items;

                for (auto & row : results)
                {
                    items.push_back(make_shared<T>(row));
                }

                return items;
            }

            template<typename V>
            bool refreshBy(const string &name, const V &value)
            {
                auto query = select_query(db(), tableName(), schema().column_names());

                query.where(format("{0} = ? LIMIT 1", name).str());

                query.bind(1, value);

                auto result = query.execute();

                if (!result.is_valid())
                    return false;

                init(*result);

                return true;
            }
        };

        template<typename T>
        map<string,shared_ptr<schema>> base_record<T>::schema_cache_;
    }

}

#endif
