project('aspeed-app', 'c', version: '1.0.0')
thread_dep = dependency('threads')

# TODO: ast-rvas
librvas = library('rvas', 'ast_rvas/rvas_lib/rvas.c', install: true, version: meson.project_version(),
    dependencies: thread_dep, include_directories: include_directories('ast_rvas/rvas_lib'))
executable('vtest', ['ast_rvas/vtest.c'], install: true, link_with: librvas,
    dependencies: thread_dep, include_directories: include_directories('ast_rvas/rvas_lib'))
executable('rvas_test', ['ast_rvas/rvas_test.c'], install: true, link_with: librvas,
    dependencies: thread_dep, include_directories: include_directories('ast_rvas/rvas_lib'))

# Video
executable('ast-video', ['video/ast-video.c', 'video/video.c'], install: true)
install_data('video/video.inf')

# i2c
executable('i2c-test', 'i2c-test/i2c-test.c', install: true,
    dependencies: thread_dep)

executable('i2c-slave-mqueue', 'i2c-slave-mqueue/i2c-slave-mqueue.c', install: true)

# i3c
executable('i3c-test', 'i3c-test/i3c-test.c', install: true)

# eSPI
executable('oob-pch-test', 'espi_test/oob-pch-test.c', install: true)
executable('mafs-test', 'espi_test/mafs-test.c', install: true)
executable('oob-test', 'espi_test/oob-test.c', install: true)
executable('perif-test', 'espi_test/perif-test.c', install: true)
executable('safs-test', 'espi_test/safs-test.c', install: true)
executable('vw-test', 'espi_test/vw-test.c', install: true)

# kcs/bt
executable('kcs_bt_test', 'kcs_bt_test/kcs_bt_test.c', install: true)

# mctp
executable('mctp', ['mctp/mctp.c', 'mctp/libmctp.c'], install: true,
    include_directories: include_directories('mctp'), dependencies: thread_dep)

# mem_utils
executable('md', ['mem_utils/md.c', 'mem_utils/mem_common.c'], install: true)
executable('mw', ['mem_utils/mw.c', 'mem_utils/mem_common.c'], install: true)
executable('spd', ['mem_utils/spd.c', 'mem_utils/mem_common.c'], install: true)
executable('spw', ['mem_utils/spw.c', 'mem_utils/mem_common.c'], install: true)

# svf
executable('svf', ['svf/main.c', 'svf/ast-jtag.c', 'svf/svf.c'], install: true)
