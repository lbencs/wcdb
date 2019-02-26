/*
 * Tencent is pleased to support the open source community by making
 * WCDB available.
 *
 * Copyright (C) 2017 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use
 * this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 *       https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __WCDB_SYNTAX_TABLE_OR_SUBQUERY_HPP
#define __WCDB_SYNTAX_TABLE_OR_SUBQUERY_HPP

#include <WCDB/SyntaxIdentifier.hpp>
#include <WCDB/SyntaxJoinClause.hpp>

namespace WCDB {

namespace Syntax {

class TableOrSubquery final : public Identifier {
#pragma mark - Lang
public:
    WCDB_DEFAULT_SYNTAX_ENUM(
        Table,
        Function,
        TableOrSubqueries,
        JoinClause,
        Select,
    );

    Schema schema;
    String tableOrFunction;
    String alias;
    enum class IndexType {
        NotSet,
        Indexed,
        NotIndexed,
    } indexType
    = IndexType::NotSet;
    String index;
    std::list<Expression> expressions;
    std::list<TableOrSubquery> tableOrSubqueries;
    JoinClause joinClause;
    SelectSTMT select;

#pragma mark - Identifier
public:
    static constexpr const Type type = Type::TableOrSubquery;
    Type getType() const override final;
    String getValidDescription() const override final;
    void iterate(const Iterator& iterator, bool& stop) override final;
};

} // namespace Syntax

} // namespace WCDB

#endif /* __WCDB_SYNTAX_TABLE_OR_SUBQUERY_HPP */
