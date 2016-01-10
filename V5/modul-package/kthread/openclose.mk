##### OPENCLOSE

OPENCLOSE_VERSION = 1.0
OPENCLOSE_SITE_METHOD = file
OPENCLOSE_NAME = kthread
OPENCLOSE_SITE = $(OPENCLOSE_NAME)-$(OPENCLOSE_VERSION).tar.gz


OPENCLOSE_DEPENDENCIES = linux

define OPENCLOSE_BUILD_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules
endef

define OPENCLOSE_INSTALL_TARGET_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules_install
	$(INSTALL) -m 0755 -D $(@D)/test_kthread.sh $(TARGET_DIR)/usr/bin/test_kthread.sh
endef

define OPENCLOSE_CLEAN_CMDS
	$(MAKE) -C $(@D) clean
endef

define OPENCLOSE_UNINSTALL_TARGET_CMS
	rm $(TARGET_DIR)/usr/bin/kthread
endef

$(eval $(generic-package))
