# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

# Unable to find any files that looked like license statements. Check the accompanying
# documentation and source headers and set LICENSE and LIC_FILES_CHKSUM accordingly.
#
# NOTE: LICENSE is being set to "CLOSED" to allow you to at least start building - if
# this is not accurate with respect to the licensing of the software being built (it
# will not be in most cases) you must specify the correct value before using this
# recipe for anything other than initial testing/development!
DESCRIPTION = "To check UART OPEN or NOT_made by YJ"
SECTION = "innowell_application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://uart-status.c"

S = "${WORKDIR}"

PV = "1.0+git${SRCPV}"

do_compile() {
${CC} ${LDFLAGS} uart-status.c -o uart-status
}

do_install() {
install -d ${D}${bindir}
install -m 0755 uart-status ${D}${bindir}
}

