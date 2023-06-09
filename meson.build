project('algoritmos_poblacion_expresiones',
		'cpp',
		version : '1.0',
		default_options : [
			'cpp_std=c++20', 
			'warning_level=3', 
			'buildtype=release'
		]		
)

compiler = meson.get_compiler('cpp')

# 
#
# Profiling
#
#

if get_option('gprof')
	add_project_arguments('-pg', language : 'cpp')
endif


# 
#
# Main library
#
#

include_dir = include_directories('include')


all_deps = []

if get_option('openmp')
	openmp_dep = dependency('openmp')
	all_deps += openmp_dep
endif

estructura_src = [
	'src/algoritmos_poblaciones/Nodo.cpp', 'include/algoritmos_poblaciones/Nodo.hpp', 
	'src/algoritmos_poblaciones/Parametros.cpp', 'include/algoritmos_poblaciones/Parametros.hpp', 
	'include/algoritmos_poblaciones/preprocesado.hpp', 
	'src/algoritmos_poblaciones/Expresion.cpp', 'include/algoritmos_poblaciones/Expresion.hpp', 
	'src/algoritmos_poblaciones/Expresion_GAP.cpp', 'include/algoritmos_poblaciones/Expresion_GAP.hpp',
	'src/algoritmos_poblaciones/aux_pob_algs.cpp', 'include/algoritmos_poblaciones/aux_pob_algs.hpp'
]

algoritmos_src = [
	'include/algoritmos_poblaciones/AlgoritmoPoblacion.hpp',
	'include/algoritmos_poblaciones/AlgoritmoPG.hpp',
	'src/algoritmos_poblaciones/AlgoritmoGA_P.cpp', 'include/algoritmos_poblaciones/AlgoritmoGA_P.hpp'
]


all_src = [estructura_src, algoritmos_src]

algoritmos_poblacion_expresiones_lib = static_library(
	'algoritmos_poblacion_expresiones',
	all_src,
	include_directories : include_dir,
	dependencies : all_deps
)

algoritmos_poblacion_expresiones_dep = declare_dependency(
	link_with : algoritmos_poblacion_expresiones_lib,
	include_directories : include_dir,
	dependencies : all_deps
)


# 
#
# Executables
#
#

argparse_dep = dependency('argparse', required : true)

main = executable(
	'main',
	'src/main.cpp',
	dependencies : [algoritmos_poblacion_expresiones_dep, argparse_dep]
)


main_evaluar_expresion_archivo = executable(
	'main_evaluar_expresion_archivo',
	'src/main_evaluar_expresion_archivo.cpp',
	dependencies : algoritmos_poblacion_expresiones_dep
)

gtest_dep = dependency('gtest')
main_test = executable(
	'main_test',
	'src/main_test.cpp',
	dependencies : [algoritmos_poblacion_expresiones_dep, gtest_dep]
)


# 
#
# Documentation
#
#

if get_option('docs')

	doxygen = find_program('doxygen', required : true)
	dot = find_program('dot', required : true)

	doxygen_conf = configuration_data()
	doxygen_conf.set('USE_MDFILE_AS_MAINPAGE',  meson.source_root() + '/README.md')
	doxygen_conf.set('INPUT',  meson.source_root() + '/README.md ' + 
								meson.source_root() + '/include ' +
								meson.source_root() + '/include/algoritmos_poblaciones ')

	doxygen_conf.set('EXAMPLE_PATH', meson.source_root() + '/src')

	doxygen_conf.set('HTML_HEADER', meson.source_root() + '/doc/doxys/styles/header.html')
	doxygen_conf.set('HTML_EXTRA_STYLESHEET', meson.source_root() + '/doc/doxys/styles/styles.css')
	doxygen_conf.set('HTML_EXTRA_FILES',  meson.source_root() + '/doc/doxys/styles/script.js ' + 
										meson.source_root() + '/doc/doxys/styles/file.png ' +
										meson.source_root() + '/doc/doxys/styles/folder.png ' + 
										meson.source_root() + '/doc/doxys/styles/folder_open.png ' +
										meson.source_root() + '/doc/doxys/styles/mermaid.min.js')



	doxyfile = configure_file(
		input : 'doc/doxys/Doxyfile',
		output : 'Doxyfile.out',
		configuration : doxygen_conf
	)


	docs = custom_target('doxygen',
					input : all_src,
					output : 'docs',
					command : [doxygen, doxyfile],
					build_by_default: true
	)
endif
