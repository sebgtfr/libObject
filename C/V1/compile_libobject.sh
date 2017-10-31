#!/bin/sh

# Debug mode
export DEBUG=on

# Debug system
export OS_SYSTEM="linux"

# List Objects
OBJECTS=("String" "Vector" "List" "Buffer" "Ini" "Timer" "Socket" "Server" "Client" "Number")
#          01        02      03      04     05     06       07      08       09        10

# List of module's states, this is associative array of OBJECTS. HERE TO ACTIVATE MODULE.
STATE_MODULE=("on" "on" "on" "on" "on" "on" "on" "on" "on" "on")
#STATE_MODULE=("off" "off" "off" "off" "off" "off" "off" "off" "off" "on")
#              01   02   03   04   05   06   07   08   09   10

NB_OBJECTS=${#OBJECTS[@]}	# Number of objects.
NB_MODULE=${#STATE_MODULE[@]}	# Number of module.
DIR_OBJECTS=()			# Array of directory to module on.
MODULE_ON=()			# Array of activate module's name.
NB_MODULE_ON=0			# Number of module on.

# Check if they are as many object as module.
if [ $NB_OBJECTS -ne $NB_MODULE ]
then
    echo "Error: Missing module's states !"
    exit
fi

# Include object to compilation.
activate_module()
{
    eval CURRENT_MODULE_STATE="$""MODULE_"${1^^}
    if [ $CURRENT_MODULE_STATE != "on" ]
    then
	NB_MODULE_ON=$((NB_MODULE_ON+1))
	MODULE_ON+=("${1}${2}")
	export "DIR_${1^^}"="${BASE_DIR_OBJECT}/$1" # Generate path's directory of current object.
	DIR_OBJECTS+=("${BASE_DIR_OBJECT}/$1") # Generate array of path's directory.
	export "MODULE_${1^^}"="on"
	STATE_MODULE["${3}"]="on"
    fi
}

# Activate module needed by module on
active_dependence_module_on()
{
    if [ "${STATE_MODULE[$INI]}" == "on" ]
    then
	activate_module ${OBJECTS[$STRING]} "(need by Ini)" $STRING		# Ini need String module.
	activate_module ${OBJECTS[$VECTOR]} "(need by Ini)" $VECTOR		# Ini need Vector module.
    fi
    if [ "${STATE_MODULE[$SERVER]}" == "on" ]
    then
	activate_module ${OBJECTS[$LIST]} "(need by Server)" $LIST		# Server need List module.
	activate_module ${OBJECTS[$TIMER]} "(need by Server)" $TIMER		# Server need List module.
	activate_module ${OBJECTS[$SOCKET]} "(need by Server)" $SOCKET		# Server need List module.
    fi
    if [ "${STATE_MODULE[$CLIENT]}" == "on" ]
    then
	activate_module ${OBJECTS[$SOCKET]} "(need by Server)" $SOCKET		# Client need Socket module.
    fi
    if [ "${STATE_MODULE[$SOCKET]}" == "on" ] &&
	[ "${STATE_MODULE[$STRING]}" != "on" ]
    then
	activate_module ${OBJECTS[$BUFFER]} "(need by Socket)" $BUFFER		# Socket need Buffer module.
    fi
    if [ "${STATE_MODULE[$LIST]}" == "on" ] && [ "${STATE_MODULE[$VECTOR]}" != "on" ]
    then
	activate_module ${OBJECTS[$VECTOR]} "(need by List)" $VECTOR		# List need Vector module.
    fi
    if [ "${STATE_MODULE[$STRING]}" == "on" ] && [ "${STATE_MODULE[$VECTOR]}" != "on" ]
    then
	activate_module ${OBJECTS[$VECTOR]} "(need by String)" $VECTOR		# String need Vector module.
    fi
}

# Generate array of objects to compile.
generate_objects()
{
    # Generate objects
    BASE_DIR_OBJECT="./Objects"
    for ((i=0; i < $NB_OBJECTS; ++i))
    do
	OBJECT_NAME=${OBJECTS[$i]} # get name of current object.
	declare -r "${OBJECT_NAME^^}"=$i
	export "MODULE_${OBJECT_NAME^^}"=${STATE_MODULE[$i]} # Generate module's state of current object.
	if [ ${STATE_MODULE[$i]} == "on" ]
	then
	    export "MODULE_${OBJECT_NAME^^}"="off"
	    activate_module $OBJECT_NAME "" $i
	fi
    done

    if [ $NB_MODULE_ON -eq 0 ]
    then
	echo "All module are off !"
	exit
    fi
    active_dependence_module_on
}

# Create release's directory.
create_release_file()
{
    export RELEASE="./release"
    export INCLUDE="$RELEASE/include"

    # Generate Release directory
    if [ -e $RELEASE ]
    then
	rm -fr $RELEASE
    fi

    # Generate include's release directory
    mkdir -p $INCLUDE
}

# Create release's directory.
export_module_on()
{
    # Export header of boolean
    cp -f "$BASE_DIR_OBJECT/Bool/bool.h" $INCLUDE

    echo "Génération de la libobject avec les modules suivants :"
    # Export header of all active module
    for ((i=0; i < $NB_MODULE_ON; ++i))
    do
	echo "- ${MODULE_ON[$i]}"
	cp -f ${DIR_OBJECTS[$i]}/include/*.h $INCLUDE
    done
}

## main

generate_objects
create_release_file
export_module_on


# Execute Makefile
make re && make clean
