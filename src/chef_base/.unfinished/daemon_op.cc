#include "daemon_op.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

namespace chef {

  int daemon_op::exist(const char *pidfile) {
    int fp = open(pidfile, O_RDONLY, 0);
    if (fp == -1) {
      return -1;
    }
    char buf[64] = {0};
    ssize_t ret = read(fp, buf, 64);
    if (ret == -1) {
      return -1;
    }
    close(fp);
    char *p = strchr(buf, '\n');
    if (p != NULL) {
      *p = '\0';
    }
    int pid = atoi(buf);
    if (pid <= 0 || kill(pid, 0) == -1) {
      return -1;
    }
    return pid;
  }

  int daemon_op::write(const char *pidfile) {
    int fp = open(pidfile, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fp == -1) {
      return -1;
    }
    if (lockf(fp, F_TLOCK, 0) < 0) {
      return -1;
    }
    char buf[64] = {0};
    pid_t pid = ::getpid();
    snprintf(buf, 64, "%d\n", pid);
    size_t len = strlen(buf);
    size_t written = ::write(fp, buf, len);
    close(fp);
    if (len != written) {
      return -1;
    }
    return pid;
  }

  int daemon_op::start(const char *pidfile) {
    int pid = exist(pidfile);
    if (pid > 0) {
      exit(1);
    }
    if (::daemon(1, 0) == -1) {
      exit(1);
    }
    pid = daemon_op::write(pidfile);
    if (pid == -1) {
      exit(1);
    }
    return pid;
  }

} // namespace chef
