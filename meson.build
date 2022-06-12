project('cpuminer', ['c', 'cpp'], meson_version: '>=0.58.0', version: files('VERSION'), default_options : ['c_std=gnu11', 'cpp_std=c++17', 'werror=false'])

# stop after 1 errors
if meson.get_compiler('cpp').get_id() == 'gcc'
    add_global_arguments(['-fmax-errors=1'], language: ['c', 'cpp']) 
    add_project_arguments(['-D_GNU_SOURCE', ], language: ['c', 'cpp']) 
endif


# define host os type for os-specific code.
host_sys = host_machine.system()
if host_sys == 'windows'
  os = '_WINDOWS_'
elif host_sys == 'linux'
  os = '_LINUX_'
elif host_sys == 'darwin'
  os = '_MAC_'
else
  error('ERROR: os [' + host_sys + '] not supported!')
endif

add_global_arguments(['-D' + os ], language: 'cpp') 


cpu = host_machine.cpu_family()

if cpu == 'x86'
  build = 32
elif cpu == 'x86_64'
  build = 64
else
  error('ERROR: cpu type ' + cpu + ' not supported!')
endif

message('DEBUG = ' + get_option('debug').to_string())
message('BUILD =' + build.to_string())

fs = import('fs')

# where to install binaries for package
install_dir = join_paths(meson.project_build_root(), 'install')

# dependencies
buildinfo_dep = dependency('build-info')

tfm_dep = dependency('tinyformat')

catch2_dep = dependency('catch2')
catch2_ex_dep = dependency('catch2-ex')
xputil_dep = dependency('xputil')
gsl_dep = dependency('gsl')
thread_dep = dependency('threads')

openssl_dep = dependency('openssl')
curl_dep = dependency('libcurl', required: true)
gmp_dep = dependency('gmp')

# link with math lib
math_dep = declare_dependency(link_args: ['-lm'])

# compat
subdir('compat')
subdir('algo')

srcs = [
    'algo-gate-api.c', 'api.c', 'cpu-miner.c', 'malloc-huge.c', 'sysinfos.c', 'util.c',
]


srcs += [
    'asm/neoscrypt_asm.S',
    'asm/sha2-x64.S', 'asm/scrypt-x64.S', 'asm/aesb-x64.S',
]


cpuminer = executable('cpuminer', srcs, 
    dependencies: [
        jansson_dep, thread_dep, curl_dep, openssl_dep, math_dep, algos_dep, gmp_dep,
    ], 
    install: true, install_dir: install_dir
)