srcs = [
    'diff_tests.cpp',
]

miner_test = executable('miner-test', srcs, include_directories: '..', dependencies: [catch2_dep, catch2_ex_dep, ])

test('miner-test', miner_test, timeout: 60)