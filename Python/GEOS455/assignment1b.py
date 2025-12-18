# /usr/bin/python3

import os, shutil, sys


def recursive_copy(source, dest):
    # scan the directory for entries
    with os.scandir(source) as listing:
        # iterate through each entry in the source directory
        for entry in listing:
            # special case to avoid infinite recursion (do not descend into
            # destination directory)
            if entry.path == dest:
                pass
            # make directories as required
            elif entry.is_dir():
                os.mkdir(dest + os.path.sep + entry.name + "_working")
                # recurse
                recursive_copy(
                    source + os.path.sep + entry.name,
                    dest + os.path.sep + entry.name + "_working",
                )
            # copy files as required
            else:
                shutil.copy(
                    source + os.path.sep + entry.name,
                    dest + os.path.sep + entry.name + "_working",
                )


# Copies all files and folders from SRC_DIR to DEST_DIR, appending "_working"
# to each entry in the destination directory.
def main():
    # source path from which all files and directories shall be copied
    # SRC_DIR = "%shome%sjonah%sDocuments%sGEOS455%sAssign1" % \
    # (os.path.sep, os.path.sep, os.path.sep, os.path.sep, os.path.sep)
    SRC_DIR = ".{}".format(os.path.sep)

    # destination path
    DEST_DIR = SRC_DIR + os.path.sep + "Working"

    # if destination directory exists, delete it
    if os.path.isdir(DEST_DIR):
        shutil.rmtree(DEST_DIR)
    # if destination path exists (but isn't a directory), tell the user and
    # exit
    elif os.path.exists(DEST_DIR):
        print(
            'A non-directory entry already exists at "%s". '
            "Please rename or delete the existing entry." % (DEST_DIR)
        )
        sys.exit(1)

    # make the working directory
    os.mkdir(DEST_DIR)

    # perform the copy operation
    recursive_copy(SRC_DIR, DEST_DIR)


if "__main__" == __name__:
    main()
