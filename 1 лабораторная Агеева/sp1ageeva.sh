echo "Package search program."
echo "A program for checking the existence of a package."
echo "Developer: Ageeva Valeria"

echo "--------------------------------------------------"

while :
do
    read -p "Enter the package name: " package

    if yum list installed "$package" ; then
       yum info "$package"
    else
        echo "$package not installed yet"

        if yum list "$package" ; then
            while : ; do
                read -p "$package exist in repository. Would you like to install it? [y/N] " flag1
                if [[ "$flag1" == "y" || "$flag1" == "Y" ]]; then
                    yum install "$package"
                elif [[ "$flag1" == "n" || "$flag1" == "N" ]]; then
                    break
                elif [[ -z "$flag1" ]]; then
                    break
                else
                    1>&2 echo "Invalid value, must be y or n"
                fi
            done
        else
            1>&2 echo "Failed to search $package in repository"
        fi
    fi

    while : ; do
        read -p "Would you like to continue? [y/N] " flag2
        if [[ "$flag2" == "y" || "$flag2" == "Y" ]]; then
            break;
        elif [[ "$flag2" == "n" || "$flag2" == "N" ]]; then
            exit "$?"
        elif [[ -z "$flag2" ]]; then
            exit "$?"
        else
            1>&2 echo "Invalid value, must be y or n"
        fi
    done
done



