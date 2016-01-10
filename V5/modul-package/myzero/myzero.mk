##### MYZERO

MYZERO_VERSION = 1.0
MYZERO_SITE_METHOD = file
MYZERO_NAME = myzero
MYZERO_SITE = $(MYZERO_NAME)-$(MYZERO_VERSION).tar.gz


MYZERO_DEPENDENCIES = linux

define MYZERO_BUILD_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules 
endef

define MYZERO_INSTALL_TARGET_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules_install
	$(INSTALL) -m 0755 -D $(@D)/test_$(MYZERO_NAME).sh $(TARGET_DIR)/usr/bin/test_$(MYZERO_NAME).sh
endef

define MYZERO_CLEAN_CMDS
	$(MAKE) -C $(@D) clean
endef

define MYZERO_UNINSTALL_TARGET_CMS
	rm $(TARGET_DIR)/usr/bin/$(MYZERO_NAME)
endef

$(eval $(generic-package))
