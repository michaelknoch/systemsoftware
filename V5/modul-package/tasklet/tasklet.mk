##### TASKLET

TASKLET_VERSION = 1.0
TASKLET_SITE_METHOD = file
TASKLET_NAME = tasklet
TASKLET_SITE = $(TASKLET_NAME)-$(TASKLET_VERSION).tar.gz


TASKLET_DEPENDENCIES = linux

define TASKLET_BUILD_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules
endef

define TASKLET_INSTALL_TARGET_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules_install
	$(INSTALL) -m 0755 -D $(@D)/test_$(TASKLET_NAME).sh $(TARGET_DIR)/usr/bin/test_$(TASKLET_NAME).sh
endef

define TASKLET_CLEAN_CMDS
	$(MAKE) -C $(@D) clean
endef

define TASKLET_UNINSTALL_TARGET_CMS
	rm $(TARGET_DIR)/usr/bin/$(TASKLET_NAME)
endef

$(eval $(generic-package))
