#include <iostream>

#include <errno.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int tun_alloc(const char *dev, char *dev_out) {
  struct ifreq ifr;
  int tun_fd, rc, dev_len;

  dev_len = strlen(dev);
  if (dev_len >= IFNAMSIZ) {
    std::cout << "dev name : " << dev << ", len is too long" << std::endl;
    return -1;
  }

  if ((tun_fd = open("/dev/net/tun", O_RDWR | O_CLOEXEC)) < 0) {
    std::cout << "opening tun device" << std::endl;
    return -1;
  }
  memset(&ifr, 0, sizeof(ifr));

  if (dev) {
    memcpy(ifr.ifr_name, dev, dev_len + 1);
  }
  ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
  rc = ioctl(tun_fd, TUNSETIFF, &ifr);

  if (rc == -1) {
    close(tun_fd);
    std::cout << "ioctl errno : " << errno << std::endl;
    return -1;
  }
  if (dev_out) {
    memcpy(dev_out, ifr.ifr_name, IFNAMSIZ);
  }
  return tun_fd;
}

int main() {
  char tun_fd_out[IFNAMSIZ];
  int tun_fd = tun_alloc("tun0", tun_fd_out);
  std::cout << tun_fd << std::endl;
  std::cout << tun_fd_out << std::endl;
  sleep(100);
}
