##https://buildroot.org/downloads/manual/manual.html#adding-packages

TEMPLATE_VERSION = 1.0
TEMPLATE_NAME = template
TEMPLATE_SITE_METHOD = file
TEMPLATE_SITE = $(TEMPLATE_NAME)-$(TEMPLATE_VERSION).tar.gz


define TEMPLATE_BUILD_CMDS
	$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules 
endef

define TEMPLATE_INSTALL_TARGET_CMDS
	#$(MAKE) $(LINUX_MAKE_FLAGS) -C $(LINUX_DIR) M=$(@D) modules_install
	$(INSTALL) -m 0755 -D $(@D)/test_template.sh $(TARGET_DIR)/usr/bin/test_template.sh
endef

define TEMPLATE_CLEAN_CMDS
	$(MAKE) -C $(@D) clean
endef

define TEMPLATE_UNINSTALL_TARGET_CMS
	rm $(TARGET_DIR)/usr/bin/$(TEMPLATE_NAME)
endef

$(eval $(generic-package))

