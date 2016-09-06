/**
 * @file   buffer.h/buffer.cc
 * @deps   nope
 *
 * @author
 *   chef <191201771@qq.com>
 *     -initial release 2016-08-31
 *
 * @brief  FIFO的流式buffer类，支持自动扩容、收缩。
 *
 */

#ifndef _CHEF_BASE_BUFFER_H_
#define _CHEF_BASE_BUFFER_H_

#include "noncopyable.hpp"
#include <stdint.h>

namespace chef {

  class buffer : public chef::copyable {
    public:
      /**
       * @param init_capacity   初始化大小，后续不够时内部会自动扩容，两倍增长
       * @param shrink_capacity
       *   收缩阀值，当申请内存大于shrink_capacity且实际使用小于init_capacity时会释发多余内存，
       *   恢复成init_capacity
       *
       */
      explicit buffer(uint64_t init_capacity = 16384, uint64_t shrink_capacity = 1048576);

      /**
       * chef::buffer(data, len);
       * 等价于
       * chef::buffer buf(len, 2 * len);
       * buf.append(data, len);
       *
       * @param data 初始化数据，内部不持有data指针
       * @param len  data长度
       *
       */
      buffer(const char *data, uint64_t len);

      ///
      ~buffer();

      /**
       * 拷贝构造以及赋值函数，内部执行深拷贝
       *
       */
      buffer(const buffer &b);
      buffer &operator=(const buffer &b);

      /** +++++++++++++++++++++++++++++++++++++++++++++++++++++
       * 往buffer填充数据有两种方法：
       * 方法一使用append函数，可填充任意大小数据，空余空间不足时自动扩容。
       *
       */
      void append(const char *buf, uint64_t len);
      /**
       * 方法二直接操作write指针，写入前需确保内部空余空间够，且操作完后需手动移动write
       * 指针位置。提供方法二是为了便于与其他字符串函数配合，在某些场景下减少一次内存拷贝。例如：
       * buf.reserve(128);
       * int len = snprintf(buf.write_pos(), 128, "name=%s,age=%d.", name, age);
       * buf.seek_write(min(len, 128));
       *
       * @function reserve
       * @param    len     确保buffer中空余空间大小>=[len],够时不做任何操作，不够则在内部扩容
       *
       * @function write_pos 返回写入位置
       *
       * @function seek_write 往后挪动写入位置
       *
       */
      void reserve(uint64_t len);
      char *write_pos() const { return data_ + write_index_; }
      void seek_write(uint64_t len);

    /** -----------------------------------------------------
     * 读取buffer中的数据
     *
     */
    char *read_pos() const { return data_ + read_index_; }
    uint64_t readable() const { return write_index_ - read_index_; }
    void erase(uint64_t len);

    /**
     * @return 找到返回key位置，失败返回NULL
     *
     */
    char *find(const char *key, int len);
    char *find(char c);
    char *find_crlf() { return find("\r\n", 2); }
    char *find_eol() { return find('\n'); }

    /**
     * 删除 '空格' '\f' '\r' '\n' '\t' '\v'
     *
     * @return this->read_pos()
     *
     */
    char *trim_left();
    char *trim_right();

    /**
     * 复位
     *
     */
    void reset();

    /**
     * 已申请内存大小
     *
     */
    uint64_t capacity() const { return capacity_; }

  public:
    #ifdef CHEF_UNIT_TEST
    uint64_t init_capacity() const { return init_capacity_; }
    uint64_t shrink_capacity() const { return shrink_capacity_; }
    uint64_t read_index() const { return read_index_; }
    uint64_t write_index() const { return write_index_; }
    char *data() const { return data_; }
    #endif // CHEF_UNIT_TEST

  private:
    const uint64_t init_capacity_;
    const uint64_t shrink_capacity_;
    uint64_t capacity_;
    uint64_t read_index_;
    uint64_t write_index_;
    char *data_;
  };

} // namespace chef

#endif // _CHEF_BASE_BUFFER_H_
