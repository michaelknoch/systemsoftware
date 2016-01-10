##### BUF

MYNULL_VERSION = 1.0
MYNULL_SITE_METHOD = file
MYNULL_NAME = buf
MYNULL_SITE = $(MYNULL_NAME)-$(MYNULL_VERSION).tar.gz


MYNULL_DEPENDENCIES = linux

define MYNULL_BUILD_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules
endef

define MYNULL_INSTALL_TARGET_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules_install
	$(INSTALL) -m 0755 -D $(@D)/test_$(MYNULL_NAME).sh $(TARGET_DIR)/usr/bin/test_$(MYNULL_NAME).sh
endef

define MYNULL_CLEAN_CMDS
	$(MAKE) -C $(@D) clean
endef

define MYNULL_UNINSTALL_TARGET_CMS
	rm $(TARGET_DIR)/usr/bin/$(MYNULL_NAME)
endef

$(eval $(generic-package))
