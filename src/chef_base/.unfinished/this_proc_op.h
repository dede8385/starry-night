/**
 * @file   this_proc_op.h/this_proc_op.cc
 * @deps   nope
 *
 * @author
 *   chef <191201771@qq.com>
 *     -initial release xxxx-xx-xx
 *
 * @brief
 *   获取当前进程相关的信息
 *
 */

#ifndef _CHEF_BASE_THIS_PROC_OP_H_
#define _CHEF_BASE_THIS_PROC_OP_H_

#include <string>
#include <stdint.h>

namespace chef {

  class this_proc_op {
    public:
      /// 读取Makefile中宏定义传入的版本号，格式为<编译时间>_<git最后一次commit号的前7位>，例如20170322212416_516ffc1
      /// 如果读取不到返回"unknown"
      static std::string version();

      /**
       * 进程启动时的unix时间戳，单位秒
       *
       */
      static int64_t boot_timestamp();

      /**
       * 进程至今运行时间，单位秒
       *
       */
      static int64_t up_duration_seconds();

      /**
       * @return 成功返回进程当前线程数，失败返回0
       *
       */
      static int32_t num_of_threads();

      /**
       * 内存管理的最小单位：物理页面的大小，单位字节
       *
       */
      static int64_t page_size();

      /**
       * 进程当前虚拟内存大小，对应top中的VIRT列，单位KBytes
       *
       */
      static int32_t virt_kb();

      /**
       * 进程当前常驻内存大小，对应top中的RES列，单位KBytes
       *
       */
      static int32_t res_kb();

      /// @return e.g. /home/chef/starry-night/build/base_test/stuff_test
      static std::string exe_filepath();

      /// @return e.g. /home/chef/starry-night/build/base_test/
      static std::string exe_path();

      /// @return e.g. stuff_test
      static std::string exe_name();

      /// content of /proc/self/status
      static std::string status();

      /// content of /proc/self/stat
      static std::string stat();

      static int32_t pid();

      static int32_t ppid();

      static int32_t uid();

      static int32_t euid();

      /// user name of os
      static std::string user_name();
  };

} // namespace chef

#endif // _CHEF_BASE_THIS_PROC_OP_H_
