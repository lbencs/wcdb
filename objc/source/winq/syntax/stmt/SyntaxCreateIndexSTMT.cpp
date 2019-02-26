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

#include <WCDB/SyntaxAssertion.hpp>
#include <WCDB/Syntax.h>

namespace WCDB {

namespace Syntax {

    bool CreateIndexSTMT::isValid() const 
    {
        return !index.empty();
    }

#pragma mark - Identifier
Identifier::Type CreateIndexSTMT::getType() const
{
    return type;
}

String CreateIndexSTMT::getValidDescription() const
{
    std::ostringstream stream;
    stream << "CREATE ";
    if (unique) {
        stream << "UNIQUE ";
    }
    stream << "INDEX ";
    if (ifNotExists) {
        stream << "IF NOT EXISTS ";
    }
    if (!schema.empty()) {
        stream << schema << ".";
    }
    stream << index << " ON " << table << "(" << indexedColumns << ")";
    if (useCondition) {
        stream << " WHERE " << condition;
    }
    return stream.str();
}

void CreateIndexSTMT::iterate(const Iterator& iterator, bool& stop)
{
    Identifier::iterate(iterator, stop);
    recursiveIterate(schema, iterator, stop);
    listIterate(indexedColumns, iterator, stop);
    if (useCondition) {
        recursiveIterate(condition, iterator, stop);
    }
}

} // namespace Syntax

} // namespace WCDB
