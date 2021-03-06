/*
 * Copyright (c) 2015, NVIDIA CORPORATION.  All rights reserved.
 * Copyright (c) 2018 CTCaer  <ctcaer@gmail.com>
 * Copyright (c) 2018-2020 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FUSEE_MTC_H_
#define FUSEE_MTC_H_

#include <stdint.h>
#include <stdbool.h>

#include "emc.h"
#include "mc.h"

#define MTC_TABLES_MAX_ENTRIES      10
#define MAX_PLL_CFGS                14

#define DVFS_FGCG_HIGH_SPEED_THRESHOLD              1000
#define IOBRICK_DCC_THRESHOLD                   2400
#define DVFS_FGCG_MID_SPEED_THRESHOLD               600

#define TEGRA21_MAX_TABLE_ID_LEN                50
#define TEGRA_EMC_ISO_USE_FREQ_MAX_NUM              12
#define PLL_C_DIRECT_FLOOR                  333500000
#define EMC_STATUS_UPDATE_TIMEOUT               1000
#define TEGRA_EMC_DEFAULT_CLK_LATENCY_US    2000

#define TEGRA_EMC_MODE_REG_17                   0x00110000
#define TEGRA_EMC_MRW_DEV_SHIFT                 30
#define TEGRA_EMC_MRW_DEV1                  2
#define TEGRA_EMC_MRW_DEV2                  1

#define EMC_CLK_EMC_2X_CLK_SRC_SHIFT                29
#define EMC_CLK_EMC_2X_CLK_SRC_MASK             \
    (0x7 << EMC_CLK_EMC_2X_CLK_SRC_SHIFT)
#define EMC_CLK_EMC_2X_CLK_DIVISOR_SHIFT            0
#define EMC_CLK_EMC_2X_CLK_DIVISOR_MASK             \
    (0xff << EMC_CLK_EMC_2X_CLK_DIVISOR_SHIFT)

enum {
    REG_MC,
    REG_EMC,
    REG_EMC0,
    REG_EMC1,
};

#define BURST_REGS_PER_CH_LIST                      \
{                                   \
    DEFINE_REG(REG_EMC0, EMC_MRW10),                \
    DEFINE_REG(REG_EMC1, EMC_MRW10),                \
    DEFINE_REG(REG_EMC0, EMC_MRW11),                \
    DEFINE_REG(REG_EMC1, EMC_MRW11),                \
    DEFINE_REG(REG_EMC0, EMC_MRW12),                \
    DEFINE_REG(REG_EMC1, EMC_MRW12),                \
    DEFINE_REG(REG_EMC0, EMC_MRW13),                \
    DEFINE_REG(REG_EMC1, EMC_MRW13),                \
}

#define BURST_REGS_LIST                         \
{                                   \
    DEFINE_REG(REG_EMC, EMC_RC),                    \
    DEFINE_REG(REG_EMC, EMC_RFC),                   \
    DEFINE_REG(REG_EMC, EMC_RFCPB),                 \
    DEFINE_REG(REG_EMC, EMC_REFCTRL2),              \
    DEFINE_REG(REG_EMC, EMC_RFC_SLR),               \
    DEFINE_REG(REG_EMC, EMC_RAS),                   \
    DEFINE_REG(REG_EMC, EMC_RP),                    \
    DEFINE_REG(REG_EMC, EMC_R2W),                   \
    DEFINE_REG(REG_EMC, EMC_W2R),                   \
    DEFINE_REG(REG_EMC, EMC_R2P),                   \
    DEFINE_REG(REG_EMC, EMC_W2P),                   \
    DEFINE_REG(REG_EMC, EMC_R2R),                   \
    DEFINE_REG(REG_EMC, EMC_TPPD),                  \
    DEFINE_REG(REG_EMC, EMC_CCDMW),                 \
    DEFINE_REG(REG_EMC, EMC_RD_RCD),                \
    DEFINE_REG(REG_EMC, EMC_WR_RCD),                \
    DEFINE_REG(REG_EMC, EMC_RRD),                   \
    DEFINE_REG(REG_EMC, EMC_REXT),                  \
    DEFINE_REG(REG_EMC, EMC_WEXT),                  \
    DEFINE_REG(REG_EMC, EMC_WDV_CHK),               \
    DEFINE_REG(REG_EMC, EMC_WDV),                   \
    DEFINE_REG(REG_EMC, EMC_WSV),                   \
    DEFINE_REG(REG_EMC, EMC_WEV),                   \
    DEFINE_REG(REG_EMC, EMC_WDV_MASK),              \
    DEFINE_REG(REG_EMC, EMC_WS_DURATION),               \
    DEFINE_REG(REG_EMC, EMC_WE_DURATION),               \
    DEFINE_REG(REG_EMC, EMC_QUSE),                  \
    DEFINE_REG(REG_EMC, EMC_QUSE_WIDTH),                \
    DEFINE_REG(REG_EMC, EMC_IBDLY),                 \
    DEFINE_REG(REG_EMC, EMC_OBDLY),                 \
    DEFINE_REG(REG_EMC, EMC_EINPUT),                \
    DEFINE_REG(REG_EMC, EMC_MRW6),                  \
    DEFINE_REG(REG_EMC, EMC_EINPUT_DURATION),           \
    DEFINE_REG(REG_EMC, EMC_PUTERM_EXTRA),              \
    DEFINE_REG(REG_EMC, EMC_PUTERM_WIDTH),              \
    DEFINE_REG(REG_EMC, EMC_QRST),                  \
    DEFINE_REG(REG_EMC, EMC_QSAFE),                 \
    DEFINE_REG(REG_EMC, EMC_RDV),                   \
    DEFINE_REG(REG_EMC, EMC_RDV_MASK),              \
    DEFINE_REG(REG_EMC, EMC_RDV_EARLY),             \
    DEFINE_REG(REG_EMC, EMC_RDV_EARLY_MASK),            \
    DEFINE_REG(REG_EMC, EMC_REFRESH),               \
    DEFINE_REG(REG_EMC, EMC_BURST_REFRESH_NUM),         \
    DEFINE_REG(REG_EMC, EMC_PRE_REFRESH_REQ_CNT),           \
    DEFINE_REG(REG_EMC, EMC_PDEX2WR),               \
    DEFINE_REG(REG_EMC, EMC_PDEX2RD),               \
    DEFINE_REG(REG_EMC, EMC_PCHG2PDEN),             \
    DEFINE_REG(REG_EMC, EMC_ACT2PDEN),              \
    DEFINE_REG(REG_EMC, EMC_AR2PDEN),               \
    DEFINE_REG(REG_EMC, EMC_RW2PDEN),               \
    DEFINE_REG(REG_EMC, EMC_CKE2PDEN),              \
    DEFINE_REG(REG_EMC, EMC_PDEX2CKE),              \
    DEFINE_REG(REG_EMC, EMC_PDEX2MRR),              \
    DEFINE_REG(REG_EMC, EMC_TXSR),                  \
    DEFINE_REG(REG_EMC, EMC_TXSRDLL),               \
    DEFINE_REG(REG_EMC, EMC_TCKE),                  \
    DEFINE_REG(REG_EMC, EMC_TCKESR),                \
    DEFINE_REG(REG_EMC, EMC_TPD),                   \
    DEFINE_REG(REG_EMC, EMC_TFAW),                  \
    DEFINE_REG(REG_EMC, EMC_TRPAB),                 \
    DEFINE_REG(REG_EMC, EMC_TCLKSTABLE),                \
    DEFINE_REG(REG_EMC, EMC_TCLKSTOP),              \
    DEFINE_REG(REG_EMC, EMC_MRW7),                  \
    DEFINE_REG(REG_EMC, EMC_TREFBW),                \
    DEFINE_REG(REG_EMC, EMC_ODT_WRITE),             \
    DEFINE_REG(REG_EMC, EMC_FBIO_CFG5),             \
    DEFINE_REG(REG_EMC, EMC_FBIO_CFG7),             \
    DEFINE_REG(REG_EMC, EMC_CFG_DIG_DLL),               \
    DEFINE_REG(REG_EMC, EMC_CFG_DIG_DLL_PERIOD),            \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_RXRT),            \
    DEFINE_REG(REG_EMC, EMC_CFG_PIPE_1),                \
    DEFINE_REG(REG_EMC, EMC_CFG_PIPE_2),                \
    DEFINE_REG(REG_EMC, EMC_PMACRO_QUSE_DDLL_RANK0_4),      \
    DEFINE_REG(REG_EMC, EMC_PMACRO_QUSE_DDLL_RANK0_5),      \
    DEFINE_REG(REG_EMC, EMC_PMACRO_QUSE_DDLL_RANK1_4),      \
    DEFINE_REG(REG_EMC, EMC_PMACRO_QUSE_DDLL_RANK1_5),      \
    DEFINE_REG(REG_EMC, EMC_MRW8),                  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_4),    \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_5),    \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQS_RANK0_0),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQS_RANK0_1),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQS_RANK0_2),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQS_RANK0_3),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQS_RANK0_4),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQS_RANK0_5),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQS_RANK1_0),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQS_RANK1_1),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQS_RANK1_2),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQS_RANK1_3),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQS_RANK1_4),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQS_RANK1_5),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_DDLL_LONG_CMD_0),        \
    DEFINE_REG(REG_EMC, EMC_PMACRO_DDLL_LONG_CMD_1),        \
    DEFINE_REG(REG_EMC, EMC_PMACRO_DDLL_LONG_CMD_2),        \
    DEFINE_REG(REG_EMC, EMC_PMACRO_DDLL_LONG_CMD_3),        \
    DEFINE_REG(REG_EMC, EMC_PMACRO_DDLL_LONG_CMD_4),        \
    DEFINE_REG(REG_EMC, EMC_PMACRO_DDLL_SHORT_CMD_0),       \
    DEFINE_REG(REG_EMC, EMC_PMACRO_DDLL_SHORT_CMD_1),       \
    DEFINE_REG(REG_EMC, EMC_PMACRO_DDLL_SHORT_CMD_2),       \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE0_3), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE1_3), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE2_3), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE3_3), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE4_3), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE5_3), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE6_3), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE7_3), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD0_3),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD1_3),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD2_3),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD3_3),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE0_3), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE1_3), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE2_3), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE3_3), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE4_3), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE5_3), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE6_3), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE7_3), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD0_0),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD0_1),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD0_2),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD0_3),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD1_0),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD1_1),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD1_2),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD1_3),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD2_0),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD2_1),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD2_2),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD2_3),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD3_0),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD3_1),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD3_2),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_CMD3_3),  \
    DEFINE_REG(REG_EMC, EMC_TXDSRVTTGEN),               \
    DEFINE_REG(REG_EMC, EMC_FDPD_CTRL_DQ),              \
    DEFINE_REG(REG_EMC, EMC_FDPD_CTRL_CMD),             \
    DEFINE_REG(REG_EMC, EMC_FBIO_SPARE),                \
    DEFINE_REG(REG_EMC, EMC_ZCAL_INTERVAL),             \
    DEFINE_REG(REG_EMC, EMC_ZCAL_WAIT_CNT),             \
    DEFINE_REG(REG_EMC, EMC_MRS_WAIT_CNT),              \
    DEFINE_REG(REG_EMC, EMC_MRS_WAIT_CNT2),             \
    DEFINE_REG(REG_EMC, EMC_AUTO_CAL_CHANNEL),          \
    DEFINE_REG(REG_EMC, EMC_DLL_CFG_0),             \
    DEFINE_REG(REG_EMC, EMC_DLL_CFG_1),             \
    DEFINE_REG(REG_EMC, EMC_PMACRO_AUTOCAL_CFG_COMMON),     \
    DEFINE_REG(REG_EMC, EMC_PMACRO_ZCTRL),              \
    DEFINE_REG(REG_EMC, EMC_CFG),                   \
    DEFINE_REG(REG_EMC, EMC_CFG_PIPE),              \
    DEFINE_REG(REG_EMC, EMC_DYN_SELF_REF_CONTROL),          \
    DEFINE_REG(REG_EMC, EMC_QPOP),                  \
    DEFINE_REG(REG_EMC, EMC_DQS_BRLSHFT_0),             \
    DEFINE_REG(REG_EMC, EMC_DQS_BRLSHFT_1),             \
    DEFINE_REG(REG_EMC, EMC_CMD_BRLSHFT_2),             \
    DEFINE_REG(REG_EMC, EMC_CMD_BRLSHFT_3),             \
    DEFINE_REG(REG_EMC, EMC_PMACRO_PAD_CFG_CTRL),           \
    DEFINE_REG(REG_EMC, EMC_PMACRO_DATA_PAD_RX_CTRL),       \
    DEFINE_REG(REG_EMC, EMC_PMACRO_CMD_PAD_RX_CTRL),        \
    DEFINE_REG(REG_EMC, EMC_PMACRO_DATA_RX_TERM_MODE),      \
    DEFINE_REG(REG_EMC, EMC_PMACRO_CMD_RX_TERM_MODE),       \
    DEFINE_REG(REG_EMC, EMC_PMACRO_CMD_PAD_TX_CTRL),        \
    DEFINE_REG(REG_EMC, EMC_PMACRO_DATA_PAD_TX_CTRL),       \
    DEFINE_REG(REG_EMC, EMC_PMACRO_COMMON_PAD_TX_CTRL),     \
    DEFINE_REG(REG_EMC, EMC_PMACRO_VTTGEN_CTRL_0),          \
    DEFINE_REG(REG_EMC, EMC_PMACRO_VTTGEN_CTRL_1),          \
    DEFINE_REG(REG_EMC, EMC_PMACRO_VTTGEN_CTRL_2),          \
    DEFINE_REG(REG_EMC, EMC_PMACRO_BRICK_CTRL_RFU1),        \
    DEFINE_REG(REG_EMC, EMC_PMACRO_CMD_BRICK_CTRL_FDPD),        \
    DEFINE_REG(REG_EMC, EMC_PMACRO_BRICK_CTRL_RFU2),        \
    DEFINE_REG(REG_EMC, EMC_PMACRO_DATA_BRICK_CTRL_FDPD),       \
    DEFINE_REG(REG_EMC, EMC_PMACRO_BG_BIAS_CTRL_0),         \
    DEFINE_REG(REG_EMC, EMC_CFG_3),                 \
    DEFINE_REG(REG_EMC, EMC_PMACRO_TX_PWRD_0),          \
    DEFINE_REG(REG_EMC, EMC_PMACRO_TX_PWRD_1),          \
    DEFINE_REG(REG_EMC, EMC_PMACRO_TX_PWRD_2),          \
    DEFINE_REG(REG_EMC, EMC_PMACRO_TX_PWRD_3),          \
    DEFINE_REG(REG_EMC, EMC_PMACRO_TX_PWRD_4),          \
    DEFINE_REG(REG_EMC, EMC_PMACRO_TX_PWRD_5),          \
    DEFINE_REG(REG_EMC, EMC_CONFIG_SAMPLE_DELAY),           \
    DEFINE_REG(REG_EMC, EMC_PMACRO_TX_SEL_CLK_SRC_0),       \
    DEFINE_REG(REG_EMC, EMC_PMACRO_TX_SEL_CLK_SRC_1),       \
    DEFINE_REG(REG_EMC, EMC_PMACRO_TX_SEL_CLK_SRC_2),       \
    DEFINE_REG(REG_EMC, EMC_PMACRO_TX_SEL_CLK_SRC_3),       \
    DEFINE_REG(REG_EMC, EMC_PMACRO_TX_SEL_CLK_SRC_4),       \
    DEFINE_REG(REG_EMC, EMC_PMACRO_TX_SEL_CLK_SRC_5),       \
    DEFINE_REG(REG_EMC, EMC_PMACRO_DDLL_BYPASS),            \
    DEFINE_REG(REG_EMC, EMC_PMACRO_DDLL_PWRD_0),            \
    DEFINE_REG(REG_EMC, EMC_PMACRO_DDLL_PWRD_1),            \
    DEFINE_REG(REG_EMC, EMC_PMACRO_DDLL_PWRD_2),            \
    DEFINE_REG(REG_EMC, EMC_PMACRO_CMD_CTRL_0),         \
    DEFINE_REG(REG_EMC, EMC_PMACRO_CMD_CTRL_1),         \
    DEFINE_REG(REG_EMC, EMC_PMACRO_CMD_CTRL_2),         \
    DEFINE_REG(REG_EMC, EMC_TR_TIMING_0),               \
    DEFINE_REG(REG_EMC, EMC_TR_DVFS),               \
    DEFINE_REG(REG_EMC, EMC_TR_CTRL_1),             \
    DEFINE_REG(REG_EMC, EMC_TR_RDV),                \
    DEFINE_REG(REG_EMC, EMC_TR_QPOP),               \
    DEFINE_REG(REG_EMC, EMC_TR_RDV_MASK),               \
    DEFINE_REG(REG_EMC, EMC_MRW14),                 \
    DEFINE_REG(REG_EMC, EMC_TR_QSAFE),              \
    DEFINE_REG(REG_EMC, EMC_TR_QRST),               \
    DEFINE_REG(REG_EMC, EMC_TRAINING_CTRL),             \
    DEFINE_REG(REG_EMC, EMC_TRAINING_SETTLE),           \
    DEFINE_REG(REG_EMC, EMC_TRAINING_VREF_SETTLE),          \
    DEFINE_REG(REG_EMC, EMC_TRAINING_CA_FINE_CTRL),         \
    DEFINE_REG(REG_EMC, EMC_TRAINING_CA_CTRL_MISC),         \
    DEFINE_REG(REG_EMC, EMC_TRAINING_CA_CTRL_MISC1),        \
    DEFINE_REG(REG_EMC, EMC_TRAINING_CA_VREF_CTRL),         \
    DEFINE_REG(REG_EMC, EMC_TRAINING_QUSE_CORS_CTRL),       \
    DEFINE_REG(REG_EMC, EMC_TRAINING_QUSE_FINE_CTRL),       \
    DEFINE_REG(REG_EMC, EMC_TRAINING_QUSE_CTRL_MISC),       \
    DEFINE_REG(REG_EMC, EMC_TRAINING_QUSE_VREF_CTRL),       \
    DEFINE_REG(REG_EMC, EMC_TRAINING_READ_FINE_CTRL),       \
    DEFINE_REG(REG_EMC, EMC_TRAINING_READ_CTRL_MISC),       \
    DEFINE_REG(REG_EMC, EMC_TRAINING_READ_VREF_CTRL),       \
    DEFINE_REG(REG_EMC, EMC_TRAINING_WRITE_FINE_CTRL),      \
    DEFINE_REG(REG_EMC, EMC_TRAINING_WRITE_CTRL_MISC),      \
    DEFINE_REG(REG_EMC, EMC_TRAINING_WRITE_VREF_CTRL),      \
    DEFINE_REG(REG_EMC, EMC_TRAINING_MPC),              \
    DEFINE_REG(REG_EMC, EMC_MRW15),                 \
}

#define TRIM_REGS_PER_CH_LIST                       \
{                                   \
    DEFINE_REG(REG_EMC0, EMC_CMD_BRLSHFT_0),            \
    DEFINE_REG(REG_EMC1, EMC_CMD_BRLSHFT_1),            \
    DEFINE_REG(REG_EMC0, EMC_DATA_BRLSHFT_0),           \
    DEFINE_REG(REG_EMC1, EMC_DATA_BRLSHFT_0),           \
    DEFINE_REG(REG_EMC0, EMC_DATA_BRLSHFT_1),           \
    DEFINE_REG(REG_EMC1, EMC_DATA_BRLSHFT_1),           \
    DEFINE_REG(REG_EMC0, EMC_QUSE_BRLSHFT_0),           \
    DEFINE_REG(REG_EMC1, EMC_QUSE_BRLSHFT_1),           \
    DEFINE_REG(REG_EMC0, EMC_QUSE_BRLSHFT_2),           \
    DEFINE_REG(REG_EMC1, EMC_QUSE_BRLSHFT_3),           \
}

#define TRIM_REGS_LIST                          \
{                                   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_LONG_DQS_RANK0_0),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_LONG_DQS_RANK0_1),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_LONG_DQS_RANK0_2),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_LONG_DQS_RANK0_3),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_LONG_DQS_RANK1_0),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_LONG_DQS_RANK1_1),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_LONG_DQS_RANK1_2),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_LONG_DQS_RANK1_3),   \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE0_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE0_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE0_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE1_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE1_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE1_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE2_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE2_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE2_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE3_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE3_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE3_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE4_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE4_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE4_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE5_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE5_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE5_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE6_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE6_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE6_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE7_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE7_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK0_BYTE7_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE0_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE0_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE0_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE1_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE1_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE1_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE2_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE2_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE2_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE3_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE3_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE3_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE4_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE4_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE4_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE5_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE5_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE5_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE6_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE6_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE6_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE7_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE7_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_DDLL_SHORT_DQ_RANK1_BYTE7_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_VREF_DQS_0),          \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_VREF_DQS_1),          \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_VREF_DQ_0),           \
    DEFINE_REG(REG_EMC, EMC_PMACRO_IB_VREF_DQ_1),           \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_0),    \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_1),    \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_2),    \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_3),    \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_4),    \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQ_RANK0_5),    \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_0),    \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_1),    \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_2),    \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_LONG_DQ_RANK1_3),    \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE0_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE0_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE0_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE1_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE1_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE1_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE2_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE2_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE2_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE3_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE3_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE3_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE4_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE4_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE4_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE5_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE5_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE5_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE6_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE6_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE6_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE7_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE7_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_BYTE7_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD0_0),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD0_1),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD0_2),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD1_0),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD1_1),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD1_2),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD2_0),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD2_1),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD2_2),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD3_0),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD3_1),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK0_CMD3_2),  \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE0_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE0_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE0_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE1_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE1_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE1_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE2_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE2_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE2_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE3_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE3_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE3_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE4_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE4_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE4_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE5_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE5_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE5_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE6_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE6_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE6_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE7_0), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE7_1), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_OB_DDLL_SHORT_DQ_RANK1_BYTE7_2), \
    DEFINE_REG(REG_EMC, EMC_PMACRO_QUSE_DDLL_RANK0_0),      \
    DEFINE_REG(REG_EMC, EMC_PMACRO_QUSE_DDLL_RANK0_1),      \
    DEFINE_REG(REG_EMC, EMC_PMACRO_QUSE_DDLL_RANK0_2),      \
    DEFINE_REG(REG_EMC, EMC_PMACRO_QUSE_DDLL_RANK0_3),      \
    DEFINE_REG(REG_EMC, EMC_PMACRO_QUSE_DDLL_RANK1_0),      \
    DEFINE_REG(REG_EMC, EMC_PMACRO_QUSE_DDLL_RANK1_1),      \
    DEFINE_REG(REG_EMC, EMC_PMACRO_QUSE_DDLL_RANK1_2),      \
    DEFINE_REG(REG_EMC, EMC_PMACRO_QUSE_DDLL_RANK1_3),      \
}

#define VREF_REGS_PER_CH_LIST                       \
{                                   \
    DEFINE_REG(REG_EMC0, EMC_TRAINING_OPT_DQS_IB_VREF_RANK0),   \
    DEFINE_REG(REG_EMC1, EMC_TRAINING_OPT_DQS_IB_VREF_RANK0),   \
    DEFINE_REG(REG_EMC0, EMC_TRAINING_OPT_DQS_IB_VREF_RANK1),   \
    DEFINE_REG(REG_EMC1, EMC_TRAINING_OPT_DQS_IB_VREF_RANK1),   \
}

#define TRAINING_MOD_REGS_PER_CH_LIST                       \
{                                   \
    DEFINE_REG(REG_EMC0, EMC_TRAINING_RW_OFFSET_IB_BYTE0),          \
    DEFINE_REG(REG_EMC1, EMC_TRAINING_RW_OFFSET_IB_BYTE0),          \
    DEFINE_REG(REG_EMC0, EMC_TRAINING_RW_OFFSET_IB_BYTE1),          \
    DEFINE_REG(REG_EMC1, EMC_TRAINING_RW_OFFSET_IB_BYTE1),          \
    DEFINE_REG(REG_EMC0, EMC_TRAINING_RW_OFFSET_IB_BYTE2),          \
    DEFINE_REG(REG_EMC1, EMC_TRAINING_RW_OFFSET_IB_BYTE2),          \
    DEFINE_REG(REG_EMC0, EMC_TRAINING_RW_OFFSET_IB_BYTE3),          \
    DEFINE_REG(REG_EMC1, EMC_TRAINING_RW_OFFSET_IB_BYTE3),          \
    DEFINE_REG(REG_EMC0, EMC_TRAINING_RW_OFFSET_IB_MISC),           \
    DEFINE_REG(REG_EMC1, EMC_TRAINING_RW_OFFSET_IB_MISC),           \
    DEFINE_REG(REG_EMC0, EMC_TRAINING_RW_OFFSET_OB_BYTE0),          \
    DEFINE_REG(REG_EMC1, EMC_TRAINING_RW_OFFSET_OB_BYTE0),          \
    DEFINE_REG(REG_EMC0, EMC_TRAINING_RW_OFFSET_OB_BYTE1),          \
    DEFINE_REG(REG_EMC1, EMC_TRAINING_RW_OFFSET_OB_BYTE1),          \
    DEFINE_REG(REG_EMC0, EMC_TRAINING_RW_OFFSET_OB_BYTE2),          \
    DEFINE_REG(REG_EMC1, EMC_TRAINING_RW_OFFSET_OB_BYTE2),          \
    DEFINE_REG(REG_EMC0, EMC_TRAINING_RW_OFFSET_OB_BYTE3),          \
    DEFINE_REG(REG_EMC1, EMC_TRAINING_RW_OFFSET_OB_BYTE3),          \
    DEFINE_REG(REG_EMC0, EMC_TRAINING_RW_OFFSET_OB_MISC),           \
    DEFINE_REG(REG_EMC1, EMC_TRAINING_RW_OFFSET_OB_MISC),           \
}

#define BURST_MC_REGS_LIST                          \
{                                   \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_CFG),    \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_OUTSTANDING_REQ),    \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_REFPB_HP_CTRL),  \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_REFPB_BANK_CTRL),    \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_TIMING_RCD), \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_TIMING_RP),  \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_TIMING_RC),  \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_TIMING_RAS), \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_TIMING_FAW), \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_TIMING_RRD), \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_TIMING_RAP2PRE), \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_TIMING_WAP2PRE), \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_TIMING_R2R), \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_TIMING_W2W), \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_TIMING_R2W), \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_TIMING_CCDMW),   \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_TIMING_W2R), \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_TIMING_RFCPB),   \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_DA_TURNS),   \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_DA_COVERS),  \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_MISC0),  \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_MISC1),  \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_MISC2),  \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_RING1_THROTTLE), \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_DHYST_CTRL), \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_DHYST_TIMEOUT_UTIL_0),   \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_DHYST_TIMEOUT_UTIL_1),   \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_DHYST_TIMEOUT_UTIL_2),   \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_DHYST_TIMEOUT_UTIL_3),   \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_DHYST_TIMEOUT_UTIL_4),   \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_DHYST_TIMEOUT_UTIL_5),   \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_DHYST_TIMEOUT_UTIL_6),   \
    DEFINE_REG(REG_MC, MC_EMEM_ARB_DHYST_TIMEOUT_UTIL_7),   \
}

#define BURST_UP_DOWN_REGS_LIST                         \
{                                   \
    DEFINE_REG(REG_MC, MC_MLL_MPCORER_PTSA_RATE),   \
    DEFINE_REG(REG_MC, MC_FTOP_PTSA_RATE),  \
    DEFINE_REG(REG_MC, MC_PTSA_GRANT_DECREMENT),    \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_XUSB_0),    \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_XUSB_1),    \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_TSEC_0),    \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_SDMMCA_0),  \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_SDMMCAA_0), \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_SDMMC_0),   \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_SDMMCAB_0), \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_PPCS_0),    \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_PPCS_1),    \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_MPCORE_0),  \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_HC_0),  \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_HC_1),  \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_AVPC_0),    \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_GPU_0), \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_GPU2_0),    \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_NVENC_0),   \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_NVDEC_0),   \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_VIC_0), \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_VI2_0), \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_ISP2_0),    \
    DEFINE_REG(REG_MC, MC_LATENCY_ALLOWANCE_ISP2_1),    \
}

#define DEFINE_REG(type, reg)   reg##_INDEX
enum BURST_REGS_LIST;
enum TRIM_REGS_LIST;
enum BURST_MC_REGS_LIST;
enum BURST_UP_DOWN_REGS_LIST;
#undef DEFINE_REG

#define DEFINE_REG(type, reg)   type##_##reg##_INDEX
enum BURST_REGS_PER_CH_LIST;
enum TRIM_REGS_PER_CH_LIST;
enum VREF_REGS_PER_CH_LIST;
enum TRAINING_MOD_REGS_PER_CH_LIST;
#undef DEFINE_REG

typedef struct {
    uint32_t rev;
    char dvfs_ver[60];
    uint32_t rate;
    uint32_t min_volt;
    uint32_t gpu_min_volt;
    char clock_src[32];
    uint32_t clk_src_emc;
    uint32_t needs_training;
    uint32_t training_pattern;
    uint32_t trained;

    uint32_t periodic_training;
    uint32_t trained_dram_clktree_c0d0u0;
    uint32_t trained_dram_clktree_c0d0u1;
    uint32_t trained_dram_clktree_c0d1u0;
    uint32_t trained_dram_clktree_c0d1u1;
    uint32_t trained_dram_clktree_c1d0u0;
    uint32_t trained_dram_clktree_c1d0u1;
    uint32_t trained_dram_clktree_c1d1u0;
    uint32_t trained_dram_clktree_c1d1u1;
    uint32_t current_dram_clktree_c0d0u0;
    uint32_t current_dram_clktree_c0d0u1;
    uint32_t current_dram_clktree_c0d1u0;
    uint32_t current_dram_clktree_c0d1u1;
    uint32_t current_dram_clktree_c1d0u0;
    uint32_t current_dram_clktree_c1d0u1;
    uint32_t current_dram_clktree_c1d1u0;
    uint32_t current_dram_clktree_c1d1u1;
    uint32_t run_clocks;
    uint32_t tree_margin;

    uint32_t num_burst;
    uint32_t num_burst_per_ch;
    uint32_t num_trim;
    uint32_t num_trim_per_ch;
    uint32_t num_mc_regs;
    uint32_t num_up_down;
    uint32_t vref_num;
    uint32_t training_mod_num;
    uint32_t dram_timing_num;

    uint32_t ptfv_list[12];

    uint32_t burst_regs[221];
    uint32_t burst_reg_per_ch[8];
    uint32_t shadow_regs_ca_train[221];
    uint32_t shadow_regs_quse_train[221];
    uint32_t shadow_regs_rdwr_train[221];

    uint32_t trim_regs[138];
    uint32_t trim_perch_regs[10];

    uint32_t vref_perch_regs[4];

    uint32_t dram_timings[5];
    uint32_t training_mod_regs[20];
    uint32_t save_restore_mod_regs[12];
    uint32_t burst_mc_regs[33];
    uint32_t la_scale_regs[24];

    uint32_t min_mrs_wait;
    uint32_t emc_mrw;
    uint32_t emc_mrw2;
    uint32_t emc_mrw3;
    uint32_t emc_mrw4;
    uint32_t emc_mrw9;
    uint32_t emc_mrs;
    uint32_t emc_emrs;
    uint32_t emc_emrs2;
    uint32_t emc_auto_cal_config;
    uint32_t emc_auto_cal_config2;
    uint32_t emc_auto_cal_config3;
    uint32_t emc_auto_cal_config4;
    uint32_t emc_auto_cal_config5;
    uint32_t emc_auto_cal_config6;
    uint32_t emc_auto_cal_config7;
    uint32_t emc_auto_cal_config8;
    uint32_t emc_cfg_2;
    uint32_t emc_sel_dpd_ctrl;
    uint32_t emc_fdpd_ctrl_cmd_no_ramp;
    uint32_t dll_clk_src;
    uint32_t clk_out_enb_x_0_clk_enb_emc_dll;
    uint32_t latency;
} tegra_emc_timing_t;

typedef struct {
    uint32_t osc_freq;
    uint32_t out_freq;
    uint32_t feedback_div;
    uint32_t input_div;
    uint32_t post_div;
} pll_cfg_t;

typedef enum {
    OP_SWITCH = 0,
    OP_TRAIN = 1,
    OP_TRAIN_SWITCH = 2
} TrainMode;

typedef enum {
    TEGRA_EMC_SRC_PLLM,
    TEGRA_EMC_SRC_PLLC,
    TEGRA_EMC_SRC_PLLP,
    TEGRA_EMC_SRC_CLKM,
    TEGRA_EMC_SRC_PLLM_UD,
    TEGRA_EMC_SRC_PLLMB_UD,
    TEGRA_EMC_SRC_PLLMB,
    TEGRA_EMC_SRC_PLLP_UD,
    TEGRA_EMC_SRC_COUNT,
} EmcSource;

enum {
    DRAM_TYPE_DDR3   = 0,
    DRAM_TYPE_LPDDR4 = 1,
    DRAM_TYPE_LPDDR2 = 2,
    DRAM_TYPE_DDR2 = 3,
};

enum {
    DLL_CHANGE_NONE = 0,
    DLL_CHANGE_ON,
    DLL_CHANGE_OFF,
};

enum {
    DLL_OFF,
    DLL_ON
};

enum {
    AUTO_PD = 0,
    MAN_SR  = 2
};

enum {
    ASSEMBLY = 0,
    ACTIVE
};

enum {
    T_RP = 0,
    T_FC_LPDDR4,
    T_RFC,
    T_PDEX,
    RL
};

enum {
    ONE_RANK = 1,
    TWO_RANK = 2
};

enum {
    SINGLE_CHANNEL = 0,
    DUAL_CHANNEL
};

enum {
    DRAM_DEV_SEL_ALL = 0,
    DRAM_DEV_SEL_0   = (2 << 30),
    DRAM_DEV_SEL_1   = (1 << 30),
};

enum {
    EMC_CFG5_QUSE_MODE_NORMAL = 0,
    EMC_CFG5_QUSE_MODE_ALWAYS_ON,
    EMC_CFG5_QUSE_MODE_INTERNAL_LPBK,
    EMC_CFG5_QUSE_MODE_PULSE_INTERN,
    EMC_CFG5_QUSE_MODE_PULSE_EXTERN,
    EMC_CFG5_QUSE_MODE_DIRECT_QUSE,
};

enum {
    DVFS_SEQUENCE = 1,
    WRITE_TRAINING_SEQUENCE = 2,
    PERIODIC_TRAINING_SEQUENCE = 3,
    DVFS_PT1 = 10,
    DVFS_UPDATE = 11,
    TRAINING_PT1 = 12,
    TRAINING_UPDATE = 13,
    PERIODIC_TRAINING_UPDATE = 14
};

enum {
    TEGRA_DRAM_OVER_TEMP_NONE = 0,
    TEGRA_DRAM_OVER_TEMP_REFRESH_X2,
    TEGRA_DRAM_OVER_TEMP_REFRESH_X4,
    TEGRA_DRAM_OVER_TEMP_THROTTLE,
    TEGRA_DRAM_OVER_TEMP_MAX,
};

/* Train all possible DRAM sequences. */
void train_dram(void);

#endif