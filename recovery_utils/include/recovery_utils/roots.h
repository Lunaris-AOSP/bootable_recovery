/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <string>

#include <fstab/fstab.h>

using Volume = android::fs_mgr::FstabEntry;

// Load and parse volume data from /etc/recovery.fstab.
void load_volume_table();

// Return the Volume* record for this mount point (or nullptr).
Volume* volume_for_mount_point(const std::string& mount_point);

// Make sure that the volume 'path' is on is mounted.  Returns 0 on
// success (volume is mounted).
int ensure_path_mounted(const std::string& path);

// Return true if the block device has a corresponding entry
// in fstab
bool BlockDevHasFstab(const std::string& path);

// Similar to ensure_path_mounted, but allows one to specify the mount_point.
int ensure_path_mounted_at(const std::string& path, const std::string& mount_point);

// Make sure that the volume 'path' is on is unmounted.  Returns 0 on
// success (volume is unmounted);
int ensure_path_unmounted(const std::string& path);

// Make sure that the volume at 'blk_device' is unmounted.
// Returns 0 on success.
int ensure_volume_unmounted(const std::string& blk_device);

// Reformat the given volume (must be the mount point only, eg
// "/cache"), no paths permitted.  Attempts to unmount the volume if
// it is mounted.
int format_volume(const std::string& volume);

// Reformat the given volume (must be the mount point only, eg
// "/cache"), no paths permitted.  Attempts to unmount the volume if
// it is mounted.
// Copies 'directory' to root of the newly formatted volume
int format_volume(const std::string& volume, const std::string& directory,
                  std::string_view new_fstype);

// Ensure that all and only the volumes that packages expect to find
// mounted (/tmp and /cache) are mounted.  Returns 0 on success.
int setup_install_mounts();

// Returns true if there is /cache in the volumes.
bool HasCache();

void map_logical_partitions();

bool logical_partitions_mapped();
