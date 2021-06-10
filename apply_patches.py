from os.path import join, isfile

Import("env")

PROJECT_LIBDEPS_DIR = env["PROJECT_LIBDEPS_DIR"]
patchflag_path = join(PROJECT_LIBDEPS_DIR, ".patching-done")

# patch file only if we didn't do it before
if not isfile(patchflag_path):
    original_file = join(PROJECT_LIBDEPS_DIR, "esp32doit-devkit-v1", "AsyncTCP", "src", "AsyncTCP.cpp")
    patch_file = join("patches", "1-AsyncTCP-xQueueCreate-size.patch")

    assert isfile(original_file) and isfile(patch_file)

    print("Partching ${original_file} with ${patch_file}")
    env.Execute("patch %s %s" % (original_file, patch_file))
    # env.Execute("touch " + patchflag_path)


    def _touch(path):
        with open(path, "w") as fp:
            fp.write("")

    env.Execute(lambda *args, **kwargs: _touch(patchflag_path))
