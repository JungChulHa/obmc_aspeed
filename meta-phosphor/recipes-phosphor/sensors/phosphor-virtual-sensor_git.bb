SUMMARY = "Virtual Sensors"
DESCRIPTION = "virtual sensors created from existing sensors and config data"
HOMEPAGE = "https://github.com/openbmc/phosphor-virtual-sensor"
PR = "r1"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=9e69ba356fa59848ffd865152a3ccc13"

inherit meson pkgconfig
inherit systemd

DEPENDS += "sdbusplus"
DEPENDS += "phosphor-dbus-interfaces"
DEPENDS += "sdeventplus"
DEPENDS += "phosphor-logging"
DEPENDS += "nlohmann-json"
DEPENDS += "exprtk"

SRC_URI = "git://github.com/openbmc/phosphor-virtual-sensor.git;protocol=git"
SRCREV = "a55a907e7220bede5f4c76ca6d99fad2a0c1f00d"
S = "${WORKDIR}/git"

SYSTEMD_SERVICE_${PN} = "phosphor-virtual-sensor.service"