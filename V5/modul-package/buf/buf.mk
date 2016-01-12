##### BUF

BUF_VERSION = 1.0
BUF_SITE_METHOD = file
BUF_NAME = buf
BUF_SITE = $(BUF_NAME)-$(BUF_VERSION).tar.gz


BUF_DEPENDENCIES = linux

define BUF_BUILD_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules
endef

define BUF_INSTALL_TARGET_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules_install
	$(INSTALL) -m 0755 -D $(@D)/test_$(BUF_NAME).sh $(TARGET_DIR)/usr/bin/test_$(BUF_NAME).sh
	$(INSTALL) -m 0755 -D $(@D)/test_$(BUF_NAME)_helper.sh $(TARGET_DIR)/usr/bin/test_$(BUF_NAME)_helper.sh
endef

define BUF_CLEAN_CMDS
	$(MAKE) -C $(@D) clean
endef

define BUF_UNINSTALL_TARGET_CMS
	rm $(TARGET_DIR)/usr/bin/$(BUF_NAME)
endef

$(eval $(generic-package))
