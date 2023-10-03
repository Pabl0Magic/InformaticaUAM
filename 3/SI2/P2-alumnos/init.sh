#!/bin/bash
cd ../P2-alumnos/P2-alumnos/P1-base
ant replegar limpiar-todo unsetup-db todo
cd ../P1-ws
ant replegar limpiar-todo unsetup-db #todo
cd ../P1-ejb-servidor-remoto
ant replegar limpiar-todo unsetup-db #todo
cd ../P1-ejb-cliente-remoto
ant replegar limpiar-todo unsetup-db #todo
