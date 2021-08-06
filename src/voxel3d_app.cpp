/*
 *  5Voxel ToF camera example
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>             /* getopt_long() */
#include <errno.h>

#include "voxel3d.h"

#define TOOLS_VER_MAJOR         (1)
#define TOOLS_VER_MINOR         (3)

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

static void mainloop(void)
{
    unsigned int count;
    int pcl_pixels = 0;
    int center_pixel_loc = TOF_DEPTH_WIDTH * (TOF_DEPTH_HEIGHT >> 1) +
                           (TOF_DEPTH_WIDTH >> 1);

    count = frame_count;

    while (count-- > 0) {
        unsigned int ret = voxel3d_queryframe(tof_depth, tof_ir);
        if (ret) {
            printf("depth center = %d (mm), IR center = %d\n",
                tof_depth[center_pixel_loc], tof_ir[center_pixel_loc]);

            pcl_pixels = voxel3d_generatePointCloud(
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
         "-p | --prod_sn          show product serial number\n"
         "-r | --get_mode         get range mode\n"
         "-R | --set_mode         set range mode\n"
         "-t | --get_conf         get confidence threshold\n"
         "-T | --set_conf         set confidence threshold\n"
         "-v | --version          show lib & firmware version\n"
         "\n",
         argv[0], TOOLS_VER_MAJOR, TOOLS_VER_MINOR, frame_count);
}

static const char short_options[] = "haA:bc:prR:tT:v";

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
    { "get_conf",          no_argument,       NULL, 't' },
    { "set_conf",          required_argument, NULL, 'T' },
    { "version",           no_argument,       NULL, 'v' },
    { 0, 0, 0, 0 }
};

int main(int argc, char **argv)
{
    char data[64];
    int  result;

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
            voxel3d_init();
            result = voxel3d_get_auto_exposure_mode();
            /*
             * function returns 0->ae_disabled; 1->ae_enabled; < 0: failed
             */
            if (result >= 0) {
                printf("Auto Exposure Mode : %s\n", (result == 0) ? "disabled" : "enabled");
            }
            voxel3d_release();
            exit(EXIT_SUCCESS);

        case 'A':
            errno = 0;
            auto_exposure_mode = strtol(optarg, NULL, 0);
            if (errno)
                errno_exit(optarg);
            voxel3d_init();
            result = voxel3d_set_auto_exposure_mode(auto_exposure_mode);
            if (result) {
                printf("Set Auto Exposure Mode : %d\n", auto_exposure_mode);
            }
            voxel3d_release();
            exit(EXIT_SUCCESS);

        case 'b':
            voxel3d_init();
            voxel3d_read_fw_build_date(data, sizeof(data));
            printf("FW build date : %s\n", data);
            voxel3d_release();
            exit(EXIT_SUCCESS);

        case 'c':
            errno = 0;
            frame_count = strtol(optarg, NULL, 0);
            if (errno)
                errno_exit(optarg);
            break;

        case 'p':
            voxel3d_init();
            voxel3d_read_prod_sn(data, sizeof(data));
            printf("Product S/N : %s\n", data);
            voxel3d_release();
            exit(EXIT_SUCCESS);

        case 'r':
            voxel3d_init();
            result = voxel3d_get_range_mode();
            if (result) {
                printf("Range Mode : %d\n", result);
            }
            voxel3d_release();
            exit(EXIT_SUCCESS);

        case 'R':
            errno = 0;
            range_mode = strtol(optarg, NULL, 0);
            if (errno)
                errno_exit(optarg);
            voxel3d_init();
            result = voxel3d_set_range_mode(range_mode);
            if (result) {
                printf("Set Rnage Mode : %d\n", range_mode);
            }
            voxel3d_release();
            exit(EXIT_SUCCESS);

        case 't':
            voxel3d_init();
            result = voxel3d_get_conf_threshold();
            printf("Confidence Threshold : %d\n", result);
            voxel3d_release();
            exit(EXIT_SUCCESS);

        case 'T':
            errno = 0;
            conf_threshold = strtol(optarg, NULL, 0);
            if (errno)
                errno_exit(optarg);
            voxel3d_init();
            result = voxel3d_set_conf_threshold(conf_threshold);
            if (result) {
                printf("Set Confidence Threshold : %d\n", conf_threshold);
            }
            voxel3d_release();
            exit(EXIT_SUCCESS);

        case 'v':
            voxel3d_init();
            voxel3d_read_lib_version(data, sizeof(data));
            printf("Share library version : %s\n", data);
            voxel3d_read_fw_version(data, sizeof(data));
            printf("5Z01A F/W version     : %s\n", data);
            voxel3d_release();
            exit(EXIT_SUCCESS);

        default:
            usage(stderr, argc, argv);
            exit(EXIT_FAILURE);
        }
    }

    /*
     * Start device
     */
    voxel3d_init();

    /*
     * main loop function
     */
    mainloop();

    /*
     * Stop device
     */
    voxel3d_release();
    return 0;
}
