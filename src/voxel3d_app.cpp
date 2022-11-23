/*
 *  5Voxel ToF camera example
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>             /* getopt_long() */
#include <errno.h>
#ifdef PLAT_WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#endif /* PLAT_WINDOWS */

#include "voxel3d.h"

#define TOOLS_VER_MAJOR         (1)
#define TOOLS_VER_MINOR         (6)

#ifdef PLAT_WINDOWS
#define SleepSeconds(x)        Sleep(x * 1000)
#else /* PLAT_LINUX */
#define SleepSeconds(x)        sleep(x)
#endif /* PLAT_WINDOWS */

static unsigned int     frame_count = 70;
static int              range_mode = 0;
static int              auto_exposure_mode = 0;
static int              conf_threshold = 35;
static unsigned short   tof_depth[TOF_DEPTH_PIXELS];
static unsigned short   tof_ir[TOF_IR_PIXELS];
static float            pointCloudXYZ[TOF_DEPTH_PIXELS * 3];

static void errno_exit(const char *s)
{
    fprintf(stderr, "%s error %d, %s\n", s, errno, strerror(errno));
    exit(EXIT_FAILURE);
}

static unsigned char fw_upgrade_cb(int state, unsigned int percent_complete)
{
    switch (state) {
    case 0:
        printf("\rFW upgrade - state: Initial             ");
        break;
    case 1:
        printf("\rFW upgrade - state: Downloading (%d%%)", percent_complete);
        break;
    case 2:
        printf("\rFW upgrade - state: Complete            ");
        break;
    default:
        printf("\rFW upgrade - state: Error               ");
        break;
    }

    return (1);
}

static void mainloop(char* dev_sn)
{
    unsigned int count;
    int pcl_pixels = 0;
    int center_pixel_loc = TOF_DEPTH_WIDTH * (TOF_DEPTH_HEIGHT >> 1) +
                           (TOF_DEPTH_WIDTH >> 1);

    count = frame_count;

    while (count > 0) {
        unsigned int ret = voxel3d_queryframe(dev_sn, tof_depth, tof_ir);
        if (ret) {
            printf("depth center = %d (mm), IR center = %d\n",
                tof_depth[center_pixel_loc], tof_ir[center_pixel_loc]);

            pcl_pixels = voxel3d_generatePointCloud(
                dev_sn,
                tof_depth,
                pointCloudXYZ);
            if (pcl_pixels) {
                printf("Pointcloud (x = %f (m), y = %f (m), z = %f (m)\n",
                        pointCloudXYZ[center_pixel_loc * 3],
                pointCloudXYZ[center_pixel_loc * 3 + 1],
                pointCloudXYZ[center_pixel_loc * 3 + 2]);
            }

            count--;
        }
    }
}

static void usage(FILE *fp, int argc, char **argv)
{
    fprintf(fp,
         "Usage: %s [options]\n\n"
         "Version %d.%d\n"
         "Options:\n"
         "-h | --help             Print this message\n"
         "-a | --get_auto_expo    get auto exposure mode\n"
         "-A | --set_auto_expo    set auto exposure mode\n"
         "-b | --build_date       show firmware build date\n"
         "-c | --count            Number of frames to grab [%i]\n"
         "-r | --get_mode         get range mode\n"
         "-R | --set_mode         set range mode\n"
         "-S | --scan_dev         scan devices and list device S/N\n"
         "-s | --dev_sn           specify device S/N to access\n"
         "-t | --get_conf         get confidence threshold\n"
         "-T | --set_conf         set confidence threshold\n"
         "-u | --fw_upgrade       device firmware upgrade\n"
         "-v | --version          show lib & firmware version\n"
         "\n",
         argv[0], TOOLS_VER_MAJOR, TOOLS_VER_MINOR, frame_count);
}

static const char short_options[] = "haA:bc:prR:Ss:tT:u:v";

static const struct option
long_options[] = {
    { "help",              no_argument,       NULL, 'h' },
    { "get_auto_expo",     no_argument,       NULL, 'a' },
    { "set_auto_expo",     required_argument, NULL, 'A' },
    { "build_date",        no_argument,       NULL, 'b' },
    { "count",             required_argument, NULL, 'c' },
    { "prod_sn",           no_argument,       NULL, 'p' },
    { "get_mode",          no_argument,       NULL, 'r' },
    { "set_mode",          required_argument, NULL, 'R' },
    { "scan_dev",          no_argument,       NULL, 'S' },
    { "dev_sn",            required_argument, NULL, 's' },
    { "get_conf",          no_argument,       NULL, 't' },
    { "set_conf",          required_argument, NULL, 'T' },
    { "fw_upgrade",        required_argument, NULL, 'u' },
    { "version",           no_argument,       NULL, 'v' },
    { 0, 0, 0, 0 }
};

int main(int argc, char **argv)
{
    int wait_time = 60;
    char data[64];
    int  result, found_device;
    CamDevInfo devInfo;
    char dev_sn[MAX_PRODUCT_SN_LEN] = {'\0'};

    for (;;) {
        int idx;
        int c;

        c = getopt_long(argc, argv,
                        short_options, long_options, &idx);

        if (-1 == c)
            break;

        switch (c) {
        case 0: /* getopt_long() flag */
            break;

        case 'h':
            usage(stdout, argc, argv);
            exit(EXIT_SUCCESS);

        case 'a':
            found_device = voxel3d_init(dev_sn);
            if (found_device > 0) {
                result = voxel3d_get_auto_exposure_mode(dev_sn);
                /*
                 * function returns 0->ae_disabled; 1->ae_enabled; < 0: failed
                 */
                if (result >= 0) {
                    printf("Auto Exposure Mode : %s\n", (result == 0) ? "disabled" : "enabled");
                }
            }
            voxel3d_release(dev_sn);
            exit(EXIT_SUCCESS);

        case 'A':
            errno = 0;
            auto_exposure_mode = strtol(optarg, NULL, 0);
            if (errno)
                errno_exit(optarg);
            found_device = voxel3d_init(dev_sn);
            if (found_device > 0) {
                result = voxel3d_set_auto_exposure_mode(dev_sn, auto_exposure_mode);
                if (result > 0) {
                    printf("Set Auto Exposure Mode : %d\n", auto_exposure_mode);
                }
            }
            voxel3d_release(dev_sn);
            exit(EXIT_SUCCESS);

        case 'b':
            found_device = voxel3d_init(dev_sn);
            if (found_device > 0) {
                memset(data, 0x0, sizeof(data));
                voxel3d_read_fw_build_date(dev_sn, data, sizeof(data));
                printf("FW build date : %s\n", data);
            }
            voxel3d_release(dev_sn);
            exit(EXIT_SUCCESS);

        case 'c':
            errno = 0;
            frame_count = strtol(optarg, NULL, 0);
            if (errno)
                errno_exit(optarg);
            break;

        case 'r':
            found_device = voxel3d_init(dev_sn);
            if (found_device > 0) {
                result = voxel3d_get_range_mode(dev_sn);
                if (result > 0) {
                    printf("Range Mode : %d\n", result);
                }
            }
            voxel3d_release(dev_sn);
            exit(EXIT_SUCCESS);

        case 'R':
            errno = 0;
            range_mode = strtol(optarg, NULL, 0);
            if (errno)
                errno_exit(optarg);

            found_device = voxel3d_init(dev_sn);
            if (found_device > 0) {
                result = voxel3d_set_range_mode(dev_sn, range_mode);
                if (result > 0) {
                    printf("Set Rnage Mode : %d\n", range_mode);
                }
            }
            voxel3d_release(dev_sn);
            exit(EXIT_SUCCESS);

        case 's':
            strncpy(dev_sn, optarg, MAX_PRODUCT_SN_LEN);
            break;

        case 'S':
            voxel3d_scan(&devInfo);
            if (devInfo.num_of_devices > 0) {
                printf("Found %d devices\n", devInfo.num_of_devices);
                for (int ix = 0; ix < devInfo.num_of_devices; ix++) {
                    printf("%d: SN = %s\n", ix, devInfo.product_sn[ix]);
                }
            }
            else {
                printf("Can't find any 5Voxel device\n");
            }
            exit(EXIT_SUCCESS);

        case 't':
            found_device = voxel3d_init(dev_sn);
            if (found_device > 0) {
                result = voxel3d_get_conf_threshold(dev_sn);
                if (result >= 0) {
                    printf("Confidence Threshold : %d\n", result);
                }
            }
            voxel3d_release(dev_sn);
            exit(EXIT_SUCCESS);

        case 'T':
            errno = 0;
            conf_threshold = strtol(optarg, NULL, 0);
            if (errno)
                errno_exit(optarg);

            found_device = voxel3d_init(dev_sn);
            if (found_device > 0) {
                result = voxel3d_set_conf_threshold(dev_sn, conf_threshold);
                if (result > 0) {
                    printf("Set Confidence Threshold : %d\n", conf_threshold);
                }
            }
            voxel3d_release(dev_sn);
            exit(EXIT_SUCCESS);
        case 'u':
            found_device = voxel3d_init(dev_sn);
            if (found_device > 0) {
                memset(data, 0x0, sizeof(data));
                voxel3d_read_fw_version(dev_sn, data, sizeof(data));
                printf("--------------------------------------------------------\n");
                printf("Before F/W upgrade\n");
                printf("F/W file     : %s\n", optarg);
                printf("F/W version  : %s\n", data);
                printf("--------------------------------------------------------\n\n");
                result = voxel3d_dev_fw_upgrade(dev_sn, optarg, fw_upgrade_cb);
                voxel3d_release(dev_sn);
                if (result < 0) {
                    printf("5Z01A FW upgrade failed\n");
                    exit(EXIT_SUCCESS);
                }

                /*
                 * Give some time for new firmware verification and reboot
                 */
                SleepSeconds(5);
                while (wait_time--) {
                    found_device = voxel3d_init(dev_sn);
                    if (found_device > 0) {
                        memset(data, 0x0, sizeof(data));
                        voxel3d_read_fw_version(dev_sn, data, sizeof(data));
                        printf("--------------------------------------------------------\n");
                        printf("After F/W upgrade\n");
                        printf("F/W version  : %s\n", data);
                        printf("--------------------------------------------------------\n\n");
                        break;
                    }
                    SleepSeconds(1);
                }
                if (wait_time == 0) {
                    printf("Time out waiting for 5Z01A device up\n");
                }
                else {
                    printf("Firmware upgrade completed\n");
                }
                voxel3d_release(dev_sn);
                exit(EXIT_SUCCESS);
            }
            break;

        case 'v':
            found_device = voxel3d_init(dev_sn);
            if (found_device > 0) {
                int ret;
                SleepSeconds(1);
                memset(data, 0x0, sizeof(data));
                ret = voxel3d_read_lib_version(data, sizeof(data));
                if (ret < 0) {
                    printf("Failed to read share library version\n");
                }
                else {
                    printf("Share library version : %s\n", data);
                }

                memset(data, 0x0, sizeof(data));
                ret = voxel3d_read_fw_version(dev_sn, data, sizeof(data));
                if (ret < 0) {
                    printf("Failed to read 5Z01A F/W version\n");
                }
                else {
                    printf("5Z01A F/W version     : %s\n", data);
                }
            }
            voxel3d_release(dev_sn);
            exit(EXIT_SUCCESS);

        default:
            usage(stderr, argc, argv);
            exit(EXIT_FAILURE);
        }
    }

    /*
     * Start device
     */
    found_device = voxel3d_init(dev_sn);

    /*
     * main loop function
     */
    if (found_device > 0) {
        mainloop(dev_sn);
    }

    /*
     * Stop device
     */
    voxel3d_release(dev_sn);
    return 0;
}
