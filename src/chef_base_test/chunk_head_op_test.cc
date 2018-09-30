#include "../base/chunk_head_op.h"
#include <string.h>
#include <stdio.h>
#include "./common/assert_wrapper.hpp"
#include "./common/check_log.hpp"

void decode_fail_test() {
  chef::chunk_head ch;
  char buf[128] = {0};
  assert(chef::chunk_head_op::decode(buf, &ch) == -1);
}

void encode_decode_test() {
  char buf[32] = "hello world";
  char raw[64];
  memcpy(raw + 24, buf, strlen(buf) + 1);
  chef::chunk_head ch;
  ch.id_ = 7;
  ch.type_ = 13;
  ch.reserved_ = 26;
  ch.body_len_ = static_cast<uint32_t>(strlen(buf) + 1);
  chef::chunk_head_op::encode(ch, raw);
  (void)ch;
  chef::chunk_head ch2;
  assert(chef::chunk_head_op::decode(raw, &ch2) == 0);
  assert(ch2.id_ == 7);
  assert(ch2.type_ == 13);
  assert(ch2.reserved_ == 26);
  assert(ch2.body_len_ == static_cast<uint32_t>(strlen(buf)) + 1);
  assert(memcmp(raw + 24, buf, ch2.body_len_) == 0);
}

int main() {
  ENTER_TEST;

  decode_fail_test();
  encode_decode_test();

  return 0;
}
