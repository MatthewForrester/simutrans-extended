#!/bin/bash

target=$1
configuration_file="config."

if [[ -n ${target} ]]
then
    echo -e "Missing configuration parameter. \n Please add the name of the configuration file you wish to use. \n For example, if your configuration file is config.linux, then enter 'simumake linux'"
else

    configuration_file="${configuration_file} ${target}"
    echo "Configuration target is ${configuration.file}"

        if [ "! -s config.linux"];
        then
            echo "Compilation failed: could not find Linux configuration file."
        else 

            cp -f config.default config.default.tmp

            if [ "! -s config.default.tmp" -o "config.default.tmp -older 1m" ];
            then
                echo "Compilation failed: could not backup config.default."	
            else
                echo "Config.default backed up."
        
                cp -f config.linux config.default
        
                if [ "! -s config.default" -o "config.default.tmp -older 1m" ];
                then
                    echo "Compilation failed: could not copy compilation configuration file"
                else
                    echo "Configuration copied."


                    branch=$(git rev-parse --abbrev-ref HEAD)

                    echo $branch

                    # make -j2 2>

                fi

            fi

        fi    

fi



