#!/bin/bash
cd ../P1-ejb-servidor-remoto
ant replegar limpiar-todo unsetup-db todo
cd ../P1-ejb-cliente-remoto
ant replegar limpiar-todo unsetup-db todo
