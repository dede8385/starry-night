/**
 * @file     chef_noncopyable.hpp
 * @deps     nope
 * @platform linux/macos/xxx
 *
 * @author
 *   chef <191201771@qq.com>
 *     - initial release xxxx-xx-xx
 *
 * @brief
 *   - class noncopyable 继承这个类，禁用拷贝构造函数、赋值函数
 *   - class copyable 空接口，继承这个类起注释强调作用说明类是可拷贝的
 *
 */

#ifndef _CHEF_BASE_NONCOPYABLE_H_
#define _CHEF_BASE_NONCOPYABLE_H_
#pragma once

namespace chef {

  class noncopyable {
    protected:
      noncopyable() {}
      virtual ~noncopyable() {}

    private:
      noncopyable(const noncopyable &);
      const noncopyable &operator=(const noncopyable &);
  };

  class copyable {};

} // namespace chef

#endif // _CHEF_BASE_NONCOPYABLE_H_
