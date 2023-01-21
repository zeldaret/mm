#!/bin/bash

# This script checks for overlay's relocs to be correctly used on the spec file depending on the overlay's NON_MATCHING/NON_EQUIVALENT
# and minimize possible broken NON_MATCHING builds.
# The script performs the following checks:
# - The extracted reloc isn't being used on the spec if the overlay has no other GLOBAL_ASM left (it has been matched).
# - Warn if an overlay is using both NON_MATCHING and NON_EQUIVALENT.
# - Warn if an overlay has NON_MATCHING ifdefs but some functions are still unattempted.
# - Both relocs (generated and extracted) are used on the spec on NON_MATCHING overlays.
# - The generated reloc isn't being used on NON_EQUIVALENT overlays.
# If any of those checks fails for any overlay, the script will print a warning and exit with a non-zero exit code.

BOLD="$(tput bold)"
RED="$(tput setaf 1)"
PURPLE="$(tput setaf 5)"
WHITE="$(tput setaf 7)"
BLINK="$(tput blink)"
RST="$(tput sgr0)"

# Run the script from the root of the project
DIR="$(dirname "$(readlink -f "$0")")"
cd "$DIR/.."

EXIT_CODE=0

OVERLAYS_SUBFOLDERS="$(find src/overlays/*/*  -type d)"

while read OVL_FOLDER; do
    # C files which are part of the current overlay
    FILES_OF_OVERLAY="$(find "$OVL_FOLDER" -name '*.c')"
    # List of files (of the current overlay) which doesn't contain GLOBAL_ASM
    FILES_WITHOUT_PRAGMA="$(grep -L '#pragma GLOBAL_ASM' ${FILES_OF_OVERLAY})"

    if [ "$FILES_OF_OVERLAY" == "$FILES_WITHOUT_PRAGMA" ]; then
        # This overlay is fully matched, so it should not be using the extracted reloc (use the generated one instead)

        OVL_NAME="$(cut -d '/' -f 4 <<< ${OVL_FOLDER})"

        # Parse the spec, searching for the extracted reloc of this overlay
        OVL_WITH_EXTRACTED_RELOC="$(grep -F "$OVL_NAME".reloc spec)"

        if [ "$OVL_WITH_EXTRACTED_RELOC" != "" ]; then
            echo "${BOLD} Matching overlay using extracted reloc on spec found: ${RED} ${OVL_FOLDER} ${RST}"
            echo "    Don't forget to change the extracted reloc to the generated one on the spec, otherwise the matched overlay won't be shiftable"
            EXIT_CODE=1
        fi
    else
        # Overlay not fully matched

        # Search for files with NON_MATCHING and NON_EQUIVALENT
        FILES_WITH_NON_MATCHING="$(grep -Fl '#ifdef NON_MATCHING' ${FILES_OF_OVERLAY})"
        FILES_WITH_NON_EQUIVALENT="$(grep -Fl '#ifdef NON_EQUIVALENT' ${FILES_OF_OVERLAY})"

        if [ "$FILES_WITH_NON_MATCHING" != "" ] && [ "$FILES_WITH_NON_EQUIVALENT" != "" ]; then
            # An overlay can't have both NON_MATCHINGs and NON_EQUIVALENTs, because relocs wouldn't be generated correctly

            echo "${BOLD} Overlay with both NON_MATCHINGs and NON_EQUIVALENTs found: ${RED} ${OVL_FOLDER} ${RST}"
            echo "    Overlays can't have both NON_MATCHING and NON_EQUIVALENT because it breaks NON_MATCHING builds"
            echo "    As an alternative you could mark NON_MATCHING functions as NON_EQUIVALENT and add a comment mentioning it is actually equivalent"
            EXIT_CODE=1

        elif [ "$FILES_WITH_NON_MATCHING" != "" ]; then
            # Overlay only contains NON_MATCHINGs

            # Get the count of NON_MATCHING and GLOBAL_ASM of the current overlay
            NON_MATCHINGS_COUNT_OF_OVERLAY="$(grep -F '#ifdef NON_MATCHING' ${FILES_WITH_NON_MATCHING} | wc -l)"
            PRAGMAS_COUNT_OF_OVERLAY="$(grep -F '#pragma GLOBAL_ASM' ${FILES_WITH_NON_MATCHING} | wc -l)"

            if [ "$NON_MATCHINGS_COUNT_OF_OVERLAY" != "$PRAGMAS_COUNT_OF_OVERLAY" ]; then
                # If an overlay uses NON_MATCHING, then every function should be either matching or marked as NON_MATCHING

                echo "${BOLD} Found an overlay with a differing number of NON_MATCHINGs and #pragma GLOBAL_ASM: ${RED} ${OVL_FOLDER} ${RST}"
                echo "    To use a NON_MATCHING check on an overlay, every function that does not match should verified to be equivalent"
                echo "    But the amount of NON_MATCHING ifdefs and GLOBAL_ASM does no match, which may suggest not every function of this overlay may have been attempted"
                EXIT_CODE=1
            fi

            OVL_NAME="$(cut -d '/' -f 4 <<< ${OVL_FOLDER})"

            # Parse the spec, searching for the extracted reloc of this overlay
            OVL_WITH_EXTRACTED_RELOC="$(grep -F "$OVL_NAME".reloc spec)"

            # Parse the spec, searching for the generated reloc of this overlay
            OVL_WITH_GENERATED_RELOC="$(grep -F "$OVL_NAME"_reloc spec)"

            if [ "$OVL_WITH_EXTRACTED_RELOC" == "" ] || [ "$OVL_WITH_GENERATED_RELOC" == "" ]; then
                # Overlays with NON_MATCHINGs should have both relocs on the spec

                echo "${BOLD} NON_MATCHING overlay missing either extracted or generated reloc on spec found: ${RED} ${OVL_FOLDER} ${RST}"
                echo "    Overlays with NON_MATCHING ifdefs must also add a NON_MATCHING ifdef on the spec to allow using the generated reloc on NON_MATCHING builds"
                EXIT_CODE=1
            fi
        elif [ "$FILES_WITH_NON_EQUIVALENT" != "" ]; then
            # Overlay only contains NON_EQUIVALENTs

            OVL_NAME="$(cut -d '/' -f 4 <<< ${OVL_FOLDER})"

            # Parse the spec, searching for the generated reloc of this overlay
            OVL_WITH_GENERATED_RELOC="$(grep -F "$OVL_NAME"_reloc spec)"

            if [ "$OVL_WITH_GENERATED_RELOC" != "" ]; then
                # Overlays with NON_EQUIVALENTs should not use a generated reloc

                echo "${BOLD} NON_EQUIVALENT overlay with generated reloc on spec found: ${RED} ${OVL_FOLDER} ${RST}"
                echo "    Overlays with NON_EQUIVALENT ifdefs can't use generated relocs"
                EXIT_CODE=1
            fi
        fi
    fi
done <<< ${OVERLAYS_SUBFOLDERS}

exit $EXIT_CODE
