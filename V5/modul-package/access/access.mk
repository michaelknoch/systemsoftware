##### OPENCLOSE

ACCESS_VERSION = 1.0
ACCESS_SITE_METHOD = file
ACCESS_NAME = access
ACCESS_SITE = $(ACCESS_NAME)-$(ACCESS_VERSION).tar.gz


ACCESS_DEPENDENCIES = linux

define ACCESS_BUILD_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) all
endef

define ACCESS_INSTALL_TARGET_CMDS
	$(INSTALL) -m 0755 -D $(@D)/$(ACCESS_NAME) $(TARGET_DIR)/usr/bin/$(ACCESS_NAME)
endef

$(eval $(generic-package))