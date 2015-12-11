##https://buildroot.org/downloads/manual/manual.html#adding-packages

LIBFOO_VERSION = 1.0
MODULE_NAME = template
LIBFOO_SOURCE = $(MODULE_NAME)-$(LIBFOO_VERSION).tar.gz


define TEMPLATE_BUILD_CMDS
	$(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D) modules
endef