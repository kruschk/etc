#!/usr/bin/python3

import os


# Create a main folder which contains a data folder, mxd folder, and output
# folder, plus any additional folders that the user desires.
def main():
    # WORKING_DIR = "%shome%sjonah%sDocuments%sGEOS455%sAssign1" % \
    # (os.path.sep, os.path.sep, os.path.sep, os.path.sep, os.path.sep)
    WORKING_DIR = ".{}".format(os.path.sep)

    # Get the names of the mandatory folders
    main_folder = input("Please enter a name for the main folder: ")
    data_folder = input("Please enter a name for the data folder: ")
    mxd_folder = input("Please enter a name for the .mxd folder: ")
    output_folder = input("Please enter a name for the data output folder: ")

    # Create the mandatory folders
    new_dir = WORKING_DIR + os.path.sep + main_folder
    os.makedirs(new_dir)
    os.mkdir(new_dir + os.path.sep + data_folder)
    os.mkdir(new_dir + os.path.sep + mxd_folder)
    os.mkdir(new_dir + os.path.sep + output_folder)

    # Create as many folders as the user would like.
    while True:
        # Determine if the user would like to create a folder and test their
        # input.
        keep_going = input(
            "Would you like to generate another subfolder? "
            'Please enter "yes" or "no": '
        )
        while "yes" != keep_going.lower() and "no" != keep_going.lower():
            keep_going = input("Invalid response. " 'Please enter "yes" or "no". ')

        # Create another folder
        if "yes" == keep_going.lower():
            subfolder = input("Please enter the name for the new folder: ")
            os.mkdir(new_dir + os.path.sep + subfolder)
        # Finish creating folders
        else:
            print("Done generating folders. Exiting program.")
            break


if "__main__" == __name__:
    main()
