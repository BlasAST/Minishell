*Este proyecto ha sido creado como parte del currículo de 42 por andtruji y bsiguenc*

# Descripción
Minishell es un proyecto que consiste en la implementación de nuestro propio shell en lenguaje C. Debe de replicar el comportamiento de Bash. 

El objetivo de realizar este proyecto es comprender como funciona una terminal por dentro y trabajar con conceptos fundamentales del sistema UNIX.

Con este proyecto hemos aprendido:

* Uso de la librería *readline* de C
* Asignación y liberación de memoria
* Manejo de ficheros y redirecciones
* Creación y sincronización de procesos usando fork's, execve, pipes, etc
* Gestión de señales del sistema
* Obtención y comprobación de códigos de salida (exit status)
* Ejecución y construcción de comandos, tanto internos como externos.
* Gestión del entorno, variables y el directorio actual
* Implementación de builtins como cd, env, pwd, unset, echo, export, unset, etc.
* Muchas otras cosas

La visión que nos aporta este proyecto es que mediante lenguaje C podemos interactuar con el sistema operativo de forma directa, siendo claro y sencillo y dandonos los conocimientos y experiencias necesarias para el correcto manejo de las cosas anteriormente mencionadas para su realización en cualquier momento.

# Instrucciones
## Instalación
Para la instalación de este proyecto es necesario la clonación del repositorio [Minishell](https://github.com/BlasAST/Minishell) ejecutando el siguiente comando:

```
git clone https://github.com/BlasAST/Minishell -o minishell

```

En caso de que tu objetivo sea el desarrollo del mismo proyecto deberás de contar con un entorno Linux para que funcione el proyecto dado que depende de llamadas al sistema como *fork, execve, pipes, señales y comportamiento POSIX*

A continuación deberás de instalar el lenguaje C para compilar el código fuente del proyecto y será compilado usando Makefile para poder crear el ejecutable. También deberás de instalar la libería de readline para que funcione correctamente.

```

sudo apt update && sudo apt upgrade -y && sudo apt install build-essential && sudo apt install make && sudo apt install libreadline-dev

```

Para comprobar su correcta instalación.

C:
```

gcc -version

```
Make:
```

make --version

```

## Compilación

Para la compilación del proyecto utilizaremos **make** que se encargara de enlazar y construir todos los archivos necesarios para la creación del ejecutable que también será generado.

Make permite tener multiples instrucciones con distintos objetivos:

Para la limpieza de todos los archivos objeto (.o) generados durante la compilación
```
make clean

```

Para la limpieza completa del proyecto (los .o y el ejecutable)
```
make fclean
```

Para una recompilación del proyecto (ejecutar make fclean y make de nuevo con un solo comando)
```
make re
```


## Ejecución
Tras la compilación del proyecto y obtener el ejecutable podemos usarlo lanzando
```
./minishell
```

Esto nos abrirá un shell interactivo donde podremos escribir comandos de Bash, ejecutar pipes(|), redirecciones (<,>,<<), ejecución de comandos externos (ls, cat, grep, etc) y comandos implementados (echo, cd, env, etc).

Para la finalización del proyecto ejecutar
```
exit
```
O usando **Control + D**


# Recursos
Para el correcto desarrollo del proyecto se ha realizado investigaciones acerca de documentación, manuales, normas e ia
* Referencias:
	* [Creación de forks](https://youtu.be/d_29asdAFUI?si=7Q87K6ECpPaza3Mg)
	* [Comunicación de Pipes](https://youtu.be/8Q9CPWuRC6o?si=j4JA3XuvRdTZGrRY)
	* [More Pipes](https://es.stackoverflow.com/questions/96529/establecer-una-comunicaci%c3%b3n-bidireccional-entre-dos-tuber%c3%adas)
	* [Librería readline](https://tiswww.case.edu/php/chet/readline/rltop.html)
	* [Makefile Tutorial](https://makefiletutorial.com/)
	* Más

Por otra parte, se ha realizado el uso de inteligencia artificial para aclaración de conceptos, explicación o aclaración de información necesaria, correción de errores tras varios intentos de solucionarlo y para el desarrollo y revisión de documentación.

