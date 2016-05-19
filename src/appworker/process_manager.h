// Copyright (c) 2015, Baidu.com, Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BAIDU_GALAXY_PROCESS_MANAGER_H
#define BAIDU_GALAXY_PROCESS_MANAGER_H

#include <string>
#include <map>
#include <vector>

#include <thread_pool.h>
#include <mutex.h>

#include "protocol/galaxy.pb.h"

namespace baidu {
namespace galaxy {

typedef proto::ProcessStatus ProcessStatus;

struct Process {
    std::string process_id;
    int32_t pid;
    ProcessStatus status;
    int32_t exit_code;
};

struct ProcessContext {
    std::string process_id;
    std::string cmd;
    std::string work_dir;
    std::vector<std::string> envs;
    bool is_deploy;
    virtual ~ProcessContext() {};
};

struct DownloadProcessContext : ProcessContext {
    std::string src_path;
    std::string dst_path;
    std::string version;
};

class ProcessManager {
public:
    ProcessManager();
    ~ProcessManager();
    int CreateProcess(const ProcessContext* context);
    int DeleteProcess(const std::string& process_id);
    int QueryProcess(const std::string& process_id, Process& process);
    void LoopWaitProcesses();

private:
    Mutex lock_;
    ThreadPool background_pool_;
    std::map<std::string, Process*> processes_;
};

} // ending namespace galaxy
} // ending namespace baidu


#endif // BAIDU_GALAXY_PROCESS_MANAGER_H
