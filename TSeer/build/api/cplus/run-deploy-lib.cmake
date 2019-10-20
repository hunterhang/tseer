#deploy lib-tar
EXECUTE_PROCESS(
WORKING_DIRECTORY /data/soft/TSeer/build/api/cplus
COMMAND cp /data/soft/TSeer/api/cplus/src/Tseer_api.h lib
COMMAND cp /data/soft/TSeer/api/cplus/src/Tseer_comm.h lib
COMMAND tar czfv  /data/soft/TSeer/build/api/cplus/Tseerapi.tgz lib
)
