/**
 * PUBLIC HEADER
 *
 * Library configuration data.
 *
 * Copyright (c) 2013 Eugene Lazin <4lazin@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


#pragma once
#include <cstdint>

extern "C" {

/** Library configuration.
 */
struct aku_Config
{
    //! Debug mode trigger
    int32_t debug_mode;

    //! Maximum depth of the late write
    int64_t max_late_write;  // TODO: move to config file

    //! Maximum cache size in bytes
    int64_t max_cache_size;  // TODO: move to config file
};

}
