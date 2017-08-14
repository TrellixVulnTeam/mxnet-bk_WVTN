/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*!
 * \file naive_storage_manager.h
 * \brief Naive storage manager.
 */
#ifndef MXNET_STORAGE_NAIVE_STORAGE_MANAGER_H_
#define MXNET_STORAGE_NAIVE_STORAGE_MANAGER_H_

#include "storage_manager.h"
#include "mxnet/base.h"

namespace mxnet {
namespace storage {

/*!
 * \brief Naive storage manager.
 */
template <class DeviceStorage>
class NaiveStorageManager final : public StorageManager {
 public:
  /*!
   * \brief Default constructor.
   */
  NaiveStorageManager() = default;
  /*!
   * \brief Default destructor.
   */
  ~NaiveStorageManager() = default;
  void* Alloc(size_t size) override;
  void Free(void* ptr, size_t) override;

  void DirectFree(void* ptr, size_t size) override {
    DeviceStorage::Free(ptr);
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(NaiveStorageManager);
};  // class NaiveStorageManager

template <class DeviceStorage>
void* NaiveStorageManager<DeviceStorage>::Alloc(size_t size) {
  return DeviceStorage::Alloc(size);
}

template <class DeviceStorage>
void NaiveStorageManager<DeviceStorage>::Free(void* ptr, size_t) {
  DeviceStorage::Free(ptr);
}

}  // namespace storage
}  // namespace mxnet

#endif  // MXNET_STORAGE_NAIVE_STORAGE_MANAGER_H_
