##### OPEN_ONCE

OPEN_ONCE_VERSION = 1.0
OPEN_ONCE_SITE_METHOD = file
OPEN_ONCE_NAME = open_once
OPEN_ONCE_SITE = $(OPEN_ONCE_NAME)-$(OPEN_ONCE_VERSION).tar.gz


OPEN_ONCE_DEPENDENCIES = linux

define OPEN_ONCE_BUILD_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules
endef

define OPEN_ONCE_INSTALL_TARGET_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules_install
	$(INSTALL) -m 0755 -D $(@D)/test_$(OPEN_ONCE_NAME).sh $(TARGET_DIR)/usr/bin/test_$(OPEN_ONCE_NAME).sh
endef

define OPEN_ONCE_CLEAN_CMDS
	$(MAKE) -C $(@D) clean
endef

define OPEN_ONCE_UNINSTALL_TARGET_CMS
	rm $(TARGET_DIR)/usr/bin/$(OPEN_ONCE_NAME)
endef

$(eval $(generic-package))
