#!/bin/bash

for i in icons/*
do
    components/esp-gui-lib/build-iconconvert-Desktop_Qt_6_4_1-Debug/iconconvert "$i" main/icons/ icon_templ.h.tmpl icon_templ.cpp.tmpl

    ICON_NAME="$(basename "$i" .png)"
    case "$ICON_NAME" in
        bobbycar|shortcircuit|logo)
            echo no grey version needed
            ;;
        *)
            components/esp-gui-lib/build-iconconvert-Desktop_Qt_6_4_1-Debug/iconconvert "$i" main/icons/ icon_templ.h.tmpl icon_templ.cpp.tmpl --background-color "#5c5c5c" --name-override "${ICON_NAME}_grey"
            ;;
    esac
done
