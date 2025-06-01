/**
 * @copyright Copyright (c) 2025 Qingsong Gou <gouqs@hotmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_SFLB32_PINCTRL_H_
#define _ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_SFLB32_PINCTRL_H_

#define SFLB32_PAD_POS  (16U)
#define SFLB32_FUNC_POS (0U)

#define SF32LB_INPUT_ENABLE_POS  (31U)
#define SF32LB_OUTPUT_ENABLE_POS (30U)
#define SF32LB_BIAS_PULL_UP_POS  (29U)
#define SF32LB_BIAS_PULL_DOWN_POS (28U)
#define SF32_OUTPUT_HIGH_POS (27U)

#define SFLSB32_PAD_MASK  0xFFFF0000
#define SFLSB32_FUNC_MASK 0x0000FFFF

#ifndef SF32LB_PINMUX
#define SF32LB_PINMUX(pad, func) ((pad << SFLB32_PAD_POS) | (func << SFLB32_FUNC_POS))
#endif

#define SFLB32_GET_PAD(pinmux)  (((pinmux) & SFLSB32_PAD_MASK) >> SFLB32_PAD_POS)
#define SFLB32_GET_FUNC(pinmux) (((pinmux) & SFLSB32_FUNC_MASK) >> SFLB32_FUNC_POS)

#define FUNC_MPI1_CLK        (1U)
#define FUNC_MPI1_CLKB       (2U)
#define FUNC_MPI1_CS         (3U)
#define FUNC_MPI1_DM         (4U)
#define FUNC_MPI1_DQS        (5U)
#define FUNC_MPI1_DQSDM      (6U)
#define FUNC_MPI1_DQSDM0     (7U)
#define FUNC_MPI1_DQSDM1     (8U)
#define FUNC_MPI1_DIO0       (9U)
#define FUNC_MPI1_DIO1       (10U)
#define FUNC_MPI1_DIO2       (11U)
#define FUNC_MPI1_DIO3       (12U)
#define FUNC_MPI1_DIO4       (13U)
#define FUNC_MPI1_DIO5       (14U)
#define FUNC_MPI1_DIO6       (15U)
#define FUNC_MPI1_DIO7       (16U)
#define FUNC_MPI1_DIO8       (17U)
#define FUNC_MPI1_DIO9       (18U)
#define FUNC_MPI1_DIO10      (19U)
#define FUNC_MPI1_DIO11      (20U)
#define FUNC_MPI1_DIO12      (21U)
#define FUNC_MPI1_DIO13      (22U)
#define FUNC_MPI1_DIO14      (23U)
#define FUNC_MPI1_DIO15      (24U)
#define FUNC_MPI2_CLK        (25U)
#define FUNC_MPI2_CLKB       (26U)
#define FUNC_MPI2_CS         (27U)
#define FUNC_MPI2_DM         (28U)
#define FUNC_MPI2_DQS        (29U)
#define FUNC_MPI2_DQSDM      (30U)
#define FUNC_MPI2_DQSDM0     (31U)
#define FUNC_MPI2_DQSDM1     (32U)
#define FUNC_MPI2_DIO0       (33U)
#define FUNC_MPI2_DIO1       (34U)
#define FUNC_MPI2_DIO2       (35U)
#define FUNC_MPI2_DIO3       (36U)
#define FUNC_MPI2_DIO4       (37U)
#define FUNC_MPI2_DIO5       (38U)
#define FUNC_MPI2_DIO6       (39U)
#define FUNC_MPI2_DIO7       (40U)
#define FUNC_MPI2_DIO8       (41U)
#define FUNC_MPI2_DIO9       (42U)
#define FUNC_MPI2_DIO10      (43U)
#define FUNC_MPI2_DIO11      (44U)
#define FUNC_MPI2_DIO12      (45U)
#define FUNC_MPI2_DIO13      (46U)
#define FUNC_MPI2_DIO14      (47U)
#define FUNC_MPI2_DIO15      (48U)
#define FUNC_MPI3_CLK        (49U)
#define FUNC_MPI3_CS         (50U)
#define FUNC_MPI3_DQS        (51U)
#define FUNC_MPI3_DIO0       (52U)
#define FUNC_MPI3_DIO1       (53U)
#define FUNC_MPI3_DIO2       (54U)
#define FUNC_MPI3_DIO3       (55U)
#define FUNC_MPI3_DIO4       (56U)
#define FUNC_MPI3_DIO5       (57U)
#define FUNC_MPI3_DIO6       (58U)
#define FUNC_MPI3_DIO7       (59U)
#define FUNC_MPI4_CLK        (60U)
#define FUNC_MPI4_CS         (61U)
#define FUNC_MPI4_DQS        (62U)
#define FUNC_MPI4_DIO0       (63U)
#define FUNC_MPI4_DIO1       (64U)
#define FUNC_MPI4_DIO2       (65U)
#define FUNC_MPI4_DIO3       (66U)
#define FUNC_MPI4_DIO4       (67U)
#define FUNC_MPI4_DIO5       (68U)
#define FUNC_MPI4_DIO6       (69U)
#define FUNC_MPI4_DIO7       (70U)
#define FUNC_MPI5_CLK        (71U)
#define FUNC_MPI5_CS         (72U)
#define FUNC_MPI5_DQS        (73U)
#define FUNC_MPI5_DIO0       (74U)
#define FUNC_MPI5_DIO1       (75U)
#define FUNC_MPI5_DIO2       (76U)
#define FUNC_MPI5_DIO3       (77U)
#define FUNC_MPI5_DIO4       (78U)
#define FUNC_MPI5_DIO5       (79U)
#define FUNC_MPI5_DIO6       (80U)
#define FUNC_MPI5_DIO7       (81U)
#define FUNC_GPIO_A0         (82U)
#define FUNC_GPIO_A1         (83U)
#define FUNC_GPIO_A2         (84U)
#define FUNC_GPIO_A3         (85U)
#define FUNC_GPIO_A4         (86U)
#define FUNC_GPIO_A5         (87U)
#define FUNC_GPIO_A6         (88U)
#define FUNC_GPIO_A7         (89U)
#define FUNC_GPIO_A8         (90U)
#define FUNC_GPIO_A9         (91U)
#define FUNC_GPIO_A10        (92U)
#define FUNC_GPIO_A11        (93U)
#define FUNC_GPIO_A12        (94U)
#define FUNC_GPIO_A13        (95U)
#define FUNC_GPIO_A14        (96U)
#define FUNC_GPIO_A15        (97U)
#define FUNC_GPIO_A16        (98U)
#define FUNC_GPIO_A17        (99U)
#define FUNC_GPIO_A18        (100U)
#define FUNC_GPIO_A19        (101U)
#define FUNC_GPIO_A20        (102U)
#define FUNC_GPIO_A21        (103U)
#define FUNC_GPIO_A22        (104U)
#define FUNC_GPIO_A23        (105U)
#define FUNC_GPIO_A24        (106U)
#define FUNC_GPIO_A25        (107U)
#define FUNC_GPIO_A26        (108U)
#define FUNC_GPIO_A27        (109U)
#define FUNC_GPIO_A28        (110U)
#define FUNC_GPIO_A29        (111U)
#define FUNC_GPIO_A30        (112U)
#define FUNC_GPIO_A31        (113U)
#define FUNC_GPIO_A32        (114U)
#define FUNC_GPIO_A33        (115U)
#define FUNC_GPIO_A34        (116U)
#define FUNC_GPIO_A35        (117U)
#define FUNC_GPIO_A36        (118U)
#define FUNC_GPIO_A37        (119U)
#define FUNC_GPIO_A38        (120U)
#define FUNC_GPIO_A39        (121U)
#define FUNC_GPIO_A40        (122U)
#define FUNC_GPIO_A41        (123U)
#define FUNC_GPIO_A42        (124U)
#define FUNC_GPIO_A43        (125U)
#define FUNC_GPIO_A44        (126U)
#define FUNC_GPIO_A45        (127U)
#define FUNC_GPIO_A46        (128U)
#define FUNC_GPIO_A47        (129U)
#define FUNC_GPIO_A48        (130U)
#define FUNC_GPIO_A49        (131U)
#define FUNC_GPIO_A50        (132U)
#define FUNC_GPIO_A51        (133U)
#define FUNC_GPIO_A52        (134U)
#define FUNC_GPIO_A53        (135U)
#define FUNC_GPIO_A54        (136U)
#define FUNC_GPIO_A55        (137U)
#define FUNC_GPIO_A56        (138U)
#define FUNC_GPIO_A57        (139U)
#define FUNC_GPIO_A58        (140U)
#define FUNC_GPIO_A59        (141U)
#define FUNC_GPIO_A60        (142U)
#define FUNC_GPIO_A61        (143U)
#define FUNC_GPIO_A62        (144U)
#define FUNC_GPIO_A63        (145U)
#define FUNC_GPIO_A64        (146U)
#define FUNC_GPIO_A65        (147U)
#define FUNC_GPIO_A66        (148U)
#define FUNC_GPIO_A67        (149U)
#define FUNC_GPIO_A68        (150U)
#define FUNC_GPIO_A69        (151U)
#define FUNC_GPIO_A70        (152U)
#define FUNC_GPIO_A71        (153U)
#define FUNC_GPIO_A72        (154U)
#define FUNC_GPIO_A73        (155U)
#define FUNC_GPIO_A74        (156U)
#define FUNC_GPIO_A75        (157U)
#define FUNC_GPIO_A76        (158U)
#define FUNC_GPIO_A77        (159U)
#define FUNC_GPIO_A78        (160U)
#define FUNC_GPIO_A79        (161U)
#define FUNC_GPIO_A80        (162U)
#define FUNC_GPIO_A81        (163U)
#define FUNC_GPIO_A82        (164U)
#define FUNC_GPIO_A83        (165U)
#define FUNC_GPIO_A84        (166U)
#define FUNC_GPIO_A85        (167U)
#define FUNC_GPIO_A86        (168U)
#define FUNC_GPIO_A87        (169U)
#define FUNC_GPIO_A88        (170U)
#define FUNC_GPIO_A89        (171U)
#define FUNC_GPIO_A90        (172U)
#define FUNC_GPIO_A91        (173U)
#define FUNC_GPIO_A92        (174U)
#define FUNC_GPIO_A93        (175U)
#define FUNC_GPIO_A94        (176U)
#define FUNC_GPIO_A95        (177U)
#define FUNC_GPIO_B0         (178U)
#define FUNC_GPIO_B1         (179U)
#define FUNC_GPIO_B2         (180U)
#define FUNC_GPIO_B3         (181U)
#define FUNC_GPIO_B4         (182U)
#define FUNC_GPIO_B5         (183U)
#define FUNC_GPIO_B6         (184U)
#define FUNC_GPIO_B7         (185U)
#define FUNC_GPIO_B8         (186U)
#define FUNC_GPIO_B9         (187U)
#define FUNC_GPIO_B10        (188U)
#define FUNC_GPIO_B11        (189U)
#define FUNC_GPIO_B12        (190U)
#define FUNC_GPIO_B13        (191U)
#define FUNC_GPIO_B14        (192U)
#define FUNC_GPIO_B15        (193U)
#define FUNC_GPIO_B16        (194U)
#define FUNC_GPIO_B17        (195U)
#define FUNC_GPIO_B18        (196U)
#define FUNC_GPIO_B19        (197U)
#define FUNC_GPIO_B20        (198U)
#define FUNC_GPIO_B21        (199U)
#define FUNC_GPIO_B22        (200U)
#define FUNC_GPIO_B23        (201U)
#define FUNC_GPIO_B24        (202U)
#define FUNC_GPIO_B25        (203U)
#define FUNC_GPIO_B26        (204U)
#define FUNC_GPIO_B27        (205U)
#define FUNC_GPIO_B28        (206U)
#define FUNC_GPIO_B29        (207U)
#define FUNC_GPIO_B30        (208U)
#define FUNC_GPIO_B31        (209U)
#define FUNC_GPIO_B32        (210U)
#define FUNC_GPIO_B33        (211U)
#define FUNC_GPIO_B34        (212U)
#define FUNC_GPIO_B35        (213U)
#define FUNC_GPIO_B36        (214U)
#define FUNC_GPIO_B37        (215U)
#define FUNC_GPIO_B38        (216U)
#define FUNC_GPIO_B39        (217U)
#define FUNC_GPIO_B40        (218U)
#define FUNC_GPIO_B41        (219U)
#define FUNC_GPIO_B42        (220U)
#define FUNC_GPIO_B43        (221U)
#define FUNC_GPIO_B44        (222U)
#define FUNC_GPIO_B45        (223U)
#define FUNC_GPIO_B46        (224U)
#define FUNC_GPIO_B47        (225U)
#define FUNC_GPIO_B48        (226U)
#define FUNC_GPIO_B49        (227U)
#define FUNC_GPIO_B50        (228U)
#define FUNC_GPIO_B51        (229U)
#define FUNC_GPIO_B52        (230U)
#define FUNC_GPIO_B53        (231U)
#define FUNC_GPIO_B54        (232U)
#define FUNC_GPIO_B55        (233U)
#define FUNC_GPIO_B56        (234U)
#define FUNC_GPIO_B57        (235U)
#define FUNC_GPIO_B58        (236U)
#define FUNC_GPIO_B59        (237U)
#define FUNC_GPIO_B60        (238U)
#define FUNC_GPIO_B61        (239U)
#define FUNC_GPIO_B62        (240U)
#define FUNC_GPIO_B63        (241U)
#define FUNC_SAIO_D0         (242U)
#define FUNC_SAIO_D1         (243U)
#define FUNC_SAIO_D2         (244U)
#define FUNC_SAIO_D3         (245U)
#define FUNC_SAIO_D4         (246U)
#define FUNC_SAIO_D5         (247U)
#define FUNC_SAIO_D6         (248U)
#define FUNC_SAIO_D7         (249U)
#define FUNC_SAIO_D8         (250U)
#define FUNC_SAIO_D9         (251U)
#define FUNC_SAIO_D10        (252U)
#define FUNC_SAIO_D11        (253U)
#define FUNC_SAIO_D12        (254U)
#define FUNC_SAIO_D13        (255U)
#define FUNC_SAIO_D14        (256U)
#define FUNC_SAIO_D15        (257U)
#define FUNC_SAIO_D16        (258U)
#define FUNC_SAIO_D17        (259U)
#define FUNC_SAIO_D18        (260U)
#define FUNC_SAIO_D19        (261U)
#define FUNC_SBIO_D0         (262U)
#define FUNC_SBIO_D1         (263U)
#define FUNC_SBIO_D2         (264U)
#define FUNC_SBIO_D3         (265U)
#define FUNC_SBIO_D4         (266U)
#define FUNC_SBIO_D5         (267U)
#define FUNC_SBIO_D6         (268U)
#define FUNC_SBIO_D7         (269U)
#define FUNC_SBIO_D8         (270U)
#define FUNC_SBIO_D9         (271U)
#define FUNC_SBIO_D10        (272U)
#define FUNC_SBIO_D11        (273U)
#define FUNC_SBIO_D12        (274U)
#define FUNC_SBIO_D13        (275U)
#define FUNC_SBIO_D14        (276U)
#define FUNC_SBIO_D15        (277U)
#define FUNC_SBIO_D16        (278U)
#define FUNC_SBIO_D17        (279U)
#define FUNC_SBIO_D18        (280U)
#define FUNC_SBIO_D19        (281U)
#define FUNC_SCIO_D0         (282U)
#define FUNC_SCIO_D1         (283U)
#define FUNC_SCIO_D2         (284U)
#define FUNC_SCIO_D3         (285U)
#define FUNC_SCIO_D4         (286U)
#define FUNC_SCIO_D5         (287U)
#define FUNC_USART1_RXD      (288U)
#define FUNC_USART1_TXD      (289U)
#define FUNC_USART1_CTS      (290U)
#define FUNC_USART1_RTS      (291U)
#define FUNC_USART2_RXD      (292U)
#define FUNC_USART2_TXD      (293U)
#define FUNC_USART2_CTS      (294U)
#define FUNC_USART2_RTS      (295U)
#define FUNC_USART3_RXD      (296U)
#define FUNC_USART3_TXD      (297U)
#define FUNC_USART3_CTS      (298U)
#define FUNC_USART3_RTS      (299U)
#define FUNC_USART4_RXD      (300U)
#define FUNC_USART4_TXD      (301U)
#define FUNC_USART4_CTS      (302U)
#define FUNC_USART4_RTS      (303U)
#define FUNC_USART5_RXD      (304U)
#define FUNC_USART5_TXD      (305U)
#define FUNC_USART5_CTS      (306U)
#define FUNC_USART5_RTS      (307U)
#define FUNC_USART6_RXD      (308U)
#define FUNC_USART6_TXD      (309U)
#define FUNC_USART6_CTS      (310U)
#define FUNC_USART6_RTS      (311U)
#define FUNC_I2C1_SCL        (312U)
#define FUNC_I2C1_SDA        (313U)
#define FUNC_I2C2_SCL        (314U)
#define FUNC_I2C2_SDA        (315U)
#define FUNC_I2C3_SCL        (316U)
#define FUNC_I2C3_SDA        (317U)
#define FUNC_I2C4_SCL        (318U)
#define FUNC_I2C4_SDA        (319U)
#define FUNC_I2C5_SCL        (320U)
#define FUNC_I2C5_SDA        (321U)
#define FUNC_I2C6_SCL        (322U)
#define FUNC_I2C6_SDA        (323U)
#define FUNC_I2C7_SCL        (324U)
#define FUNC_I2C7_SDA        (325U)
#define FUNC_SPI1_CLK        (326U)
#define FUNC_SPI1_CS         (327U)
#define FUNC_SPI1_DI         (328U)
#define FUNC_SPI1_DIO        (329U)
#define FUNC_SPI2_CLK        (330U)
#define FUNC_SPI2_CS         (331U)
#define FUNC_SPI2_DI         (332U)
#define FUNC_SPI2_DIO        (333U)

#define FUNC_LCDC1_SPI_CS    (334U)
#define FUNC_LCDC1_SPI_CLK   (335U)
#define FUNC_LCDC1_SPI_DIO0  (336U)
#define FUNC_LCDC1_SPI_DIO1  (337U)
#define FUNC_LCDC1_SPI_DIO2  (338U)
#define FUNC_LCDC1_SPI_DIO3  (339U)
#define FUNC_LCDC1_SPI_RSTB  (340U)
#define FUNC_LCDC1_SPI_TE    (341U)
#define FUNC_LCDC2_SPI_CS    (342U)
#define FUNC_LCDC2_SPI_CLK   (343U)
#define FUNC_LCDC2_SPI_DIO0  (344U)
#define FUNC_LCDC2_SPI_DIO1  (345U)
#define FUNC_LCDC2_SPI_DIO2  (346U)
#define FUNC_LCDC2_SPI_DIO3  (347U)
#define FUNC_LCDC2_SPI_RSTB  (348U)
#define FUNC_LCDC2_SPI_TE    (349U)
#define FUNC_LCDC1_8080_WR   (350U)
#define FUNC_LCDC1_8080_CS   (351U)
#define FUNC_LCDC1_8080_DIO0 (352U)
#define FUNC_LCDC1_8080_DIO1 (353U)
#define FUNC_LCDC1_8080_DIO2 (354U)
#define FUNC_LCDC1_8080_DIO3 (355U)
#define FUNC_LCDC1_8080_DIO4 (356U)
#define FUNC_LCDC1_8080_DIO5 (357U)
#define FUNC_LCDC1_8080_DIO6 (358U)
#define FUNC_LCDC1_8080_DIO7 (359U)
#define FUNC_LCDC1_8080_RD   (360U)
#define FUNC_LCDC1_8080_DC   (361U)
#define FUNC_LCDC1_8080_RSTB (362U)
#define FUNC_LCDC1_8080_TE   (363U)
#define FUNC_LCDC1_DPI_CLK   (364U)
#define FUNC_LCDC1_DPI_DE    (365U)
#define FUNC_LCDC1_DPI_SD    (366U)
#define FUNC_LCDC1_DPI_CM    (367U)
#define FUNC_LCDC1_DPI_HSYNC (368U)
#define FUNC_LCDC1_DPI_VSYNC (369U)
#define FUNC_LCDC1_DPI_R7    (370U)
#define FUNC_LCDC1_DPI_R6    (371U)
#define FUNC_LCDC1_DPI_R5    (372U)
#define FUNC_LCDC1_DPI_R4    (373U)
#define FUNC_LCDC1_DPI_R3    (374U)
#define FUNC_LCDC1_DPI_R2    (375U)
#define FUNC_LCDC1_DPI_R1    (376U)
#define FUNC_LCDC1_DPI_R0    (377U)
#define FUNC_LCDC1_DPI_G7    (378U)
#define FUNC_LCDC1_DPI_G6    (379U)
#define FUNC_LCDC1_DPI_G5    (380U)
#define FUNC_LCDC1_DPI_G4    (381U)
#define FUNC_LCDC1_DPI_G3    (382U)
#define FUNC_LCDC1_DPI_G2    (383U)
#define FUNC_LCDC1_DPI_G1    (384U)
#define FUNC_LCDC1_DPI_G0    (385U)
#define FUNC_LCDC1_DPI_B7    (386U)
#define FUNC_LCDC1_DPI_B6    (387U)
#define FUNC_LCDC1_DPI_B5    (388U)
#define FUNC_LCDC1_DPI_B4    (389U)
#define FUNC_LCDC1_DPI_B3    (390U)
#define FUNC_LCDC1_DPI_B2    (391U)
#define FUNC_LCDC1_DPI_B1    (392U)
#define FUNC_LCDC1_DPI_B0    (393U)
#define FUNC_LCDC1_JDI_SCLK  (394U)
#define FUNC_LCDC1_JDI_SCS   (395U)
#define FUNC_LCDC1_JDI_SO    (396U)
#define FUNC_LCDC1_JDI_DISP  (397U)
#define FUNC_LCDC1_JDI_EXTCOMIN (398U)
#define FUNC_LCDC1_JDI_XRST  (399U)
#define FUNC_LCDC1_JDI_VCK   (400U)
#define FUNC_LCDC1_JDI_VST   (401U)
#define FUNC_LCDC1_JDI_ENB   (402U)
#define FUNC_LCDC1_JDI_HCK   (403U)
#define FUNC_LCDC1_JDI_HST   (404U)

#define FUNC_LCDC1_JDI_R1    (405U)
#define FUNC_LCDC1_JDI_R2    (406U)
#define FUNC_LCDC1_JDI_G1    (407U)
#define FUNC_LCDC1_JDI_G2    (408U)
#define FUNC_LCDC1_JDI_B1    (409U)
#define FUNC_LCDC1_JDI_B2    (410U)
#define FUNC_LCDC1_JDI_FRP   (411U)
#define FUNC_LCDC1_JDI_XFRP  (412U)
#define FUNC_LCDC1_JDI_VCOM  (413U)

#define FUNC_LCDC2_JDI_SCLK  (414U)
#define FUNC_LCDC2_JDI_SCS   (415U)
#define FUNC_LCDC2_JDI_SO    (416U)
#define FUNC_LCDC2_JDI_DISP  (417U)
#define FUNC_LCDC2_JDI_EXTCOMIN (418U)
#define FUNC_LCDC2_JDI_XRST  (419U)
#define FUNC_LCDC2_JDI_VCK   (420U)
#define FUNC_LCDC2_JDI_VST   (421U)
#define FUNC_LCDC2_JDI_ENB   (422U)
#define FUNC_LCDC2_JDI_HCK   (423U)
#define FUNC_LCDC2_JDI_HST   (424U)
#define FUNC_LCDC2_JDI_R1    (425U)
#define FUNC_LCDC2_JDI_R2    (426U)
#define FUNC_LCDC2_JDI_G1    (427U)
#define FUNC_LCDC2_JDI_G2    (428U)
#define FUNC_LCDC2_JDI_B1    (429U)
#define FUNC_LCDC2_JDI_B2    (430U)
#define FUNC_LCDC2_JDI_FRP   (431U)
#define FUNC_LCDC2_JDI_XFRP  (432U)
#define FUNC_LCDC2_JDI_VCOM  (433U)

#define FUNC_SD1_CLK         (434U)
#define FUNC_SD1_CLKIN       (435U)
#define FUNC_SD1_CMD         (436U)
#define FUNC_SD1_DIO0        (437U)
#define FUNC_SD1_DIO1        (438U)
#define FUNC_SD1_DIO2        (439U)
#define FUNC_SD1_DIO3        (440U)
#define FUNC_SD1_DIO4        (441U)
#define FUNC_SD1_DIO5        (442U)
#define FUNC_SD1_DIO6        (443U)
#define FUNC_SD1_DIO7        (444U)
#define FUNC_SD2_CLK         (445U)
#define FUNC_SD2_CLKIN       (446U)
#define FUNC_SD2_CMD         (447U)
#define FUNC_SD2_DIO0        (448U)
#define FUNC_SD2_DIO1        (449U)
#define FUNC_SD2_DIO2        (450U)
#define FUNC_SD2_DIO3        (451U)
#define FUNC_I2S1_BCK        (452U)
#define FUNC_I2S1_LRCK       (453U)
#define FUNC_I2S1_MCLK       (454U)
#define FUNC_I2S1_SDI        (455U)
#define FUNC_I2S1_SDO        (456U)
#define FUNC_I2S2_BCK        (457U)
#define FUNC_I2S2_LRCK       (458U)
#define FUNC_I2S2_MCLK       (459U)
#define FUNC_I2S2_SDI        (460U)
#define FUNC_I2S2_SDO        (461U)
#define FUNC_I2S3_BCK        (462U)
#define FUNC_I2S3_LRCK       (463U)
#define FUNC_I2S3_MCLK       (464U)
#define FUNC_I2S3_SDI        (465U)
#define FUNC_I2S3_SDO        (466U)
#define FUNC_AUD_CLK_EXT     (467U)
#define FUNC_PDM1_CLK        (468U)
#define FUNC_PDM1_DATA       (469U)
#define FUNC_PDM2_CLK        (470U)
#define FUNC_PDM2_DATA       (471U)
#define FUNC_GPTIM1_CH1      (472U)
#define FUNC_GPTIM1_CH2      (473U)
#define FUNC_GPTIM1_CH3      (474U)
#define FUNC_GPTIM1_CH4      (475U)
#define FUNC_GPTIM1_ETR      (476U)
#define FUNC_GPTIM2_CH1      (477U)
#define FUNC_GPTIM2_CH2      (478U)
#define FUNC_GPTIM2_CH3      (479U)
#define FUNC_GPTIM2_CH4      (480U)
#define FUNC_GPTIM2_ETR      (481U)
#define FUNC_GPTIM3_CH1      (482U)
#define FUNC_GPTIM3_CH2      (483U)
#define FUNC_GPTIM3_CH3      (484U)
#define FUNC_GPTIM3_CH4      (485U)
#define FUNC_GPTIM3_ETR      (486U)
#define FUNC_GPTIM4_CH1      (487U)
#define FUNC_GPTIM4_CH2      (488U)
#define FUNC_GPTIM4_CH3      (489U)
#define FUNC_GPTIM4_CH4      (490U)
#define FUNC_GPTIM4_ETR      (491U)
#define FUNC_GPTIM5_CH1      (492U)
#define FUNC_GPTIM5_CH2      (493U)
#define FUNC_GPTIM5_CH3      (494U)
#define FUNC_GPTIM5_CH4      (495U)
#define FUNC_GPTIM5_ETR      (496U)
#define FUNC_ATIM1_CH1       (497U)
#define FUNC_ATIM1_CH1N      (498U)
#define FUNC_ATIM1_CH2       (499U)
#define FUNC_ATIM1_CH2N      (500U)
#define FUNC_ATIM1_CH3       (501U)
#define FUNC_ATIM1_CH3N      (502U)
#define FUNC_ATIM1_CH4       (503U)
#define FUNC_ATIM1_ETR       (504U)
#define FUNC_ATIM1_BKIN      (505U)
#define FUNC_ATIM1_BKIN2     (506U)
#define FUNC_ATIM2_CH1       (507U)
#define FUNC_ATIM2_CH1N      (508U)
#define FUNC_ATIM2_CH2       (509U)
#define FUNC_ATIM2_CH2N      (510U)
#define FUNC_ATIM2_CH3       (511U)
#define FUNC_ATIM2_CH3N      (512U)
#define FUNC_ATIM2_CH4       (513U)
#define FUNC_ATIM2_ETR       (514U)
#define FUNC_ATIM2_BKIN      (515U)
#define FUNC_ATIM2_BKIN2     (516U)
#define FUNC_LPTIM1_IN       (517U)
#define FUNC_LPTIM1_OUT      (518U)
#define FUNC_LPTIM1_ETR      (519U)
#define FUNC_LPTIM2_IN       (520U)
#define FUNC_LPTIM2_OUT      (521U)
#define FUNC_LPTIM2_ETR      (522U)
#define FUNC_LPTIM3_IN       (523U)
#define FUNC_LPTIM3_OUT      (524U)
#define FUNC_LPTIM3_ETR      (525U)
#define FUNC_LPCOMP1_OUT     (526U)
#define FUNC_LPCOMP2_OUT     (527U)
#define FUNC_SCI_RST         (528U)
#define FUNC_SCI_CLK         (529U)
#define FUNC_SCI_DIO         (530U)
#define FUNC_CAN1_RXD        (531U)
#define FUNC_CAN1_TXD        (532U)
#define FUNC_CAN1_STBY       (533U)
#define FUNC_CAN2_RXD        (534U)
#define FUNC_CAN2_TXD        (535U)
#define FUNC_CAN2_STBY       (536U)
#define FUNC_SWCLK           (537U)
#define FUNC_SWDIO           (538U)
#define FUNC_TWI_CLK         (539U)
#define FUNC_TWI_DIO         (540U)
#define FUNC_BT_ACTIVE       (541U)
#define FUNC_WLAN_ACTIVE     (542U)
#define FUNC_BT_PRIORITY     (543U)
#define FUNC_BT_COLLISION    (544U)
#define FUNC_SCAN_CLK        (545U)
#define FUNC_SCAN_RSTB       (546U)
#define FUNC_SCAN_EN         (547U)
#define FUNC_EDT_CLK         (548U)
#define FUNC_EDT_UPDATE      (549U)
#define FUNC_EDT_BYPASS      (550U)
#define FUNC_EDT_CHANNEL_IN0 (551U)
#define FUNC_EDT_CHANNEL_IN1 (552U)
#define FUNC_EDT_CHANNEL_IN2 (553U)
#define FUNC_EDT_CHANNEL_IN3 (554U)
#define FUNC_EDT_CHANNEL_IN4 (555U)
#define FUNC_EDT_CHANNEL_IN5 (556U)
#define FUNC_EDT_CHANNEL_IN6 (557U)
#define FUNC_EDT_CHANNEL_IN7 (558U)
#define FUNC_EDT_CHANNEL_OUT0 (559U)
#define FUNC_EDT_CHANNEL_OUT1 (560U)
#define FUNC_EDT_CHANNEL_OUT2 (561U)
#define FUNC_EDT_CHANNEL_OUT3 (562U)
#define FUNC_EDT_CHANNEL_OUT4 (563U)
#define FUNC_EDT_CHANNEL_OUT5 (564U)
#define FUNC_EDT_CHANNEL_OUT6 (565U)
#define FUNC_EDT_CHANNEL_OUT7 (566U)
#define FUNC_BIST_CLK        (567U)
#define FUNC_BIST_RST        (568U)
#define FUNC_BIST_FAIL       (569U)
#define FUNC_BIST_DONE       (570U)
#define FUNC_DBG_DO0         (571U)
#define FUNC_DBG_DO1         (572U)
#define FUNC_DBG_DO2         (573U)
#define FUNC_DBG_DO3         (574U)
#define FUNC_DBG_DO4         (575U)
#define FUNC_DBG_DO5         (576U)
#define FUNC_DBG_DO6         (577U)
#define FUNC_DBG_DO7         (578U)
#define FUNC_DBG_DO8         (579U)
#define FUNC_DBG_DO9         (580U)
#define FUNC_DBG_DO10        (581U)
#define FUNC_DBG_DO11        (582U)
#define FUNC_DBG_DO12        (583U)
#define FUNC_DBG_DO13        (584U)
#define FUNC_DBG_DO14        (585U)
#define FUNC_DBG_DO15        (586U)
#define FUNC_DBG_CLK         (587U)
#define FUNC_EXT_S_TX_EN     (588U)
#define FUNC_EXT_S_RX_EN     (589U)
#define FUNC_EXT_S_LE_2M     (590U)
#define FUNC_EXT_S_LE_MODE   (591U)
#define FUNC_EXT_S_TX_BIT0   (592U)
#define FUNC_EXT_S_TX_BIT1   (593U)
#define FUNC_EXT_S_TX_BIT2   (594U)
#define FUNC_EXT_S_TX_FLAG   (595U)
#define FUNC_EXT_S_EDR2_MODE (596U)
#define FUNC_EXT_S_EDR3_MODE (597U)
#define FUNC_EXT_S_BR_LAST_BIT (598U)
#define FUNC_EXT_S_EDR_LAST_BIT (599U)
#define FUNC_EXT_S_EDR_BIT_FLAG (600U)
#define FUNC_EXT_S_RAMP_UP_IND (601U)
#define FUNC_EXT_S_EDR_EN    (602U)
#define FUNC_EXT_S_SYNC_CLK  (603U)
#define FUNC_EXT_S_SYNC_DAT  (604U)
#define FUNC_EXT_S_SCLK      (605U)
#define FUNC_EXT_S_SDO       (606U)
#define FUNC_EXT_S_RX_BIT0   (607U)
#define FUNC_EXT_S_RX_BIT1   (608U)
#define FUNC_EXT_S_RX_BIT2   (609U)
#define FUNC_EXT_S_RX_FLAG   (610U)
#define FUNC_PA00_TIM        (611U)
#define FUNC_PA01_TIM        (612U)
#define FUNC_PA02_TIM        (613U)
#define FUNC_PA03_TIM        (614U)
#define FUNC_PA04_TIM        (615U)
#define FUNC_PA05_TIM        (616U)
#define FUNC_PA06_TIM        (617U)
#define FUNC_PA07_TIM        (618U)
#define FUNC_PA08_TIM        (619U)
#define FUNC_PA09_TIM        (620U)
#define FUNC_PA10_TIM        (621U)
#define FUNC_PA11_TIM        (622U)
#define FUNC_PA12_TIM        (623U)
#define FUNC_PA13_TIM        (624U)
#define FUNC_PA14_TIM        (625U)
#define FUNC_PA15_TIM        (626U)
#define FUNC_PA16_TIM        (627U)
#define FUNC_PA17_TIM        (628U)
#define FUNC_PA18_TIM        (629U)
#define FUNC_PA19_TIM        (630U)
#define FUNC_PA20_TIM        (631U)
#define FUNC_PA21_TIM        (632U)
#define FUNC_PA22_TIM        (633U)
#define FUNC_PA23_TIM        (634U)
#define FUNC_PA24_TIM        (635U)
#define FUNC_PA25_TIM        (636U)
#define FUNC_PA26_TIM        (637U)
#define FUNC_PA27_TIM        (638U)
#define FUNC_PA28_TIM        (639U)
#define FUNC_PA29_TIM        (640U)
#define FUNC_PA30_TIM        (641U)
#define FUNC_PA31_TIM        (642U)
#define FUNC_PA32_TIM        (643U)
#define FUNC_PA33_TIM        (644U)
#define FUNC_PA34_TIM        (645U)
#define FUNC_PA35_TIM        (646U)
#define FUNC_PA36_TIM        (647U)
#define FUNC_PA37_TIM        (648U)
#define FUNC_PA38_TIM        (649U)
#define FUNC_PA39_TIM        (650U)
#define FUNC_PA40_TIM        (651U)
#define FUNC_PA41_TIM        (652U)
#define FUNC_PA42_TIM        (653U)
#define FUNC_PA43_TIM        (654U)
#define FUNC_PA44_TIM        (655U)
#define FUNC_PA45_TIM        (656U)
#define FUNC_PA46_TIM        (657U)
#define FUNC_PA47_TIM        (658U)
#define FUNC_PA48_TIM        (659U)
#define FUNC_PA49_TIM        (660U)
#define FUNC_PA50_TIM        (661U)
#define FUNC_PA51_TIM        (662U)
#define FUNC_PA52_TIM        (663U)
#define FUNC_PA53_TIM        (664U)
#define FUNC_PA54_TIM        (665U)
#define FUNC_PA55_TIM        (666U)
#define FUNC_PA56_TIM        (667U)
#define FUNC_PA57_TIM        (668U)
#define FUNC_PA58_TIM        (669U)
#define FUNC_PA59_TIM        (670U)
#define FUNC_PA60_TIM        (671U)
#define FUNC_PA61_TIM        (672U)
#define FUNC_PA62_TIM        (673U)
#define FUNC_PA63_TIM        (674U)
#define FUNC_PA64_TIM        (675U)
#define FUNC_PA65_TIM        (676U)
#define FUNC_PA66_TIM        (677U)
#define FUNC_PA67_TIM        (678U)
#define FUNC_PA68_TIM        (679U)
#define FUNC_PA69_TIM        (680U)
#define FUNC_PA70_TIM        (681U)
#define FUNC_PA71_TIM        (682U)
#define FUNC_PA72_TIM        (683U)
#define FUNC_PA73_TIM        (684U)
#define FUNC_PA74_TIM        (685U)
#define FUNC_PA75_TIM        (686U)
#define FUNC_PA76_TIM        (687U)
#define FUNC_PA77_TIM        (688U)
#define FUNC_PA78_TIM        (689U)
#define FUNC_PA00_I2C_UART   (690U)
#define FUNC_PA01_I2C_UART   (691U)
#define FUNC_PA02_I2C_UART   (692U)
#define FUNC_PA03_I2C_UART   (693U)
#define FUNC_PA04_I2C_UART   (694U)
#define FUNC_PA05_I2C_UART   (695U)
#define FUNC_PA06_I2C_UART   (696U)
#define FUNC_PA07_I2C_UART   (697U)
#define FUNC_PA08_I2C_UART   (698U)
#define FUNC_PA09_I2C_UART   (699U)
#define FUNC_PA10_I2C_UART   (700U)
#define FUNC_PA11_I2C_UART   (701U)
#define FUNC_PA12_I2C_UART   (702U)
#define FUNC_PA13_I2C_UART   (703U)
#define FUNC_PA14_I2C_UART   (704U)
#define FUNC_PA15_I2C_UART   (705U)
#define FUNC_PA16_I2C_UART   (706U)
#define FUNC_PA17_I2C_UART   (707U)
#define FUNC_PA18_I2C_UART   (708U)
#define FUNC_PA19_I2C_UART   (709U)
#define FUNC_PA20_I2C_UART   (710U)
#define FUNC_PA21_I2C_UART   (711U)
#define FUNC_PA22_I2C_UART   (712U)
#define FUNC_PA23_I2C_UART   (713U)
#define FUNC_PA24_I2C_UART   (714U)
#define FUNC_PA25_I2C_UART   (715U)
#define FUNC_PA26_I2C_UART   (716U)
#define FUNC_PA27_I2C_UART   (717U)
#define FUNC_PA28_I2C_UART   (718U)
#define FUNC_PA29_I2C_UART   (719U)
#define FUNC_PA30_I2C_UART   (720U)
#define FUNC_PA31_I2C_UART   (721U)
#define FUNC_PA32_I2C_UART   (722U)
#define FUNC_PA33_I2C_UART   (723U)
#define FUNC_PA34_I2C_UART   (724U)
#define FUNC_PA35_I2C_UART   (725U)
#define FUNC_PA36_I2C_UART   (726U)
#define FUNC_PA37_I2C_UART   (727U)
#define FUNC_PA38_I2C_UART   (728U)
#define FUNC_PA39_I2C_UART   (729U)
#define FUNC_PA40_I2C_UART   (730U)
#define FUNC_PA41_I2C_UART   (731U)
#define FUNC_PA42_I2C_UART   (732U)
#define FUNC_PA43_I2C_UART   (733U)
#define FUNC_PA44_I2C_UART   (734U)
#define FUNC_PA45_I2C_UART   (735U)
#define FUNC_PA46_I2C_UART   (736U)
#define FUNC_PA47_I2C_UART   (737U)
#define FUNC_PA48_I2C_UART   (738U)
#define FUNC_PA49_I2C_UART   (739U)
#define FUNC_PA50_I2C_UART   (740U)
#define FUNC_PA51_I2C_UART   (741U)
#define FUNC_PA52_I2C_UART   (742U)
#define FUNC_PA53_I2C_UART   (743U)
#define FUNC_PA54_I2C_UART   (744U)
#define FUNC_PA55_I2C_UART   (745U)
#define FUNC_PA56_I2C_UART   (746U)
#define FUNC_PA57_I2C_UART   (747U)
#define FUNC_PA58_I2C_UART   (748U)
#define FUNC_PA59_I2C_UART   (749U)
#define FUNC_PA60_I2C_UART   (750U)
#define FUNC_PA61_I2C_UART   (751U)
#define FUNC_PA62_I2C_UART   (752U)
#define FUNC_PA63_I2C_UART   (753U)
#define FUNC_PA64_I2C_UART   (754U)
#define FUNC_PA65_I2C_UART   (755U)
#define FUNC_PA66_I2C_UART   (756U)
#define FUNC_PA67_I2C_UART   (757U)
#define FUNC_PA68_I2C_UART   (758U)
#define FUNC_PA69_I2C_UART   (759U)
#define FUNC_PA70_I2C_UART   (760U)
#define FUNC_PA71_I2C_UART   (761U)
#define FUNC_PA72_I2C_UART   (762U)
#define FUNC_PA73_I2C_UART   (763U)
#define FUNC_PA74_I2C_UART   (764U)
#define FUNC_PA75_I2C_UART   (765U)
#define FUNC_PA76_I2C_UART   (766U)
#define FUNC_PA77_I2C_UART   (767U)
#define FUNC_PA78_I2C_UART   (768U)
#define FUNC_PB00_TIM        (769U)
#define FUNC_PB01_TIM        (770U)
#define FUNC_PB02_TIM        (771U)
#define FUNC_PB03_TIM        (772U)
#define FUNC_PB04_TIM        (773U)
#define FUNC_PB05_TIM        (774U)
#define FUNC_PB06_TIM        (775U)
#define FUNC_PB07_TIM        (776U)
#define FUNC_PB08_TIM        (777U)
#define FUNC_PB09_TIM        (778U)
#define FUNC_PB10_TIM        (779U)
#define FUNC_PB11_TIM        (780U)
#define FUNC_PB12_TIM        (781U)
#define FUNC_PB13_TIM        (782U)
#define FUNC_PB14_TIM        (783U)
#define FUNC_PB15_TIM        (784U)
#define FUNC_PB16_TIM        (785U)
#define FUNC_PB17_TIM        (786U)
#define FUNC_PB18_TIM        (787U)
#define FUNC_PB19_TIM        (788U)
#define FUNC_PB20_TIM        (789U)
#define FUNC_PB21_TIM        (790U)
#define FUNC_PB22_TIM        (791U)
#define FUNC_PB23_TIM        (792U)
#define FUNC_PB24_TIM        (793U)
#define FUNC_PB25_TIM        (794U)
#define FUNC_PB26_TIM        (795U)
#define FUNC_PB27_TIM        (796U)
#define FUNC_PB28_TIM        (797U)
#define FUNC_PB29_TIM        (798U)
#define FUNC_PB30_TIM        (799U)
#define FUNC_PB31_TIM        (800U)
#define FUNC_PB00_UART       (801U)
#define FUNC_PB01_UART       (802U)
#define FUNC_PB02_UART       (803U)
#define FUNC_PB03_UART       (804U)
#define FUNC_PB04_UART       (805U)
#define FUNC_PB05_UART       (806U)
#define FUNC_PB06_UART       (807U)
#define FUNC_PB07_UART       (808U)
#define FUNC_PB08_UART       (809U)
#define FUNC_PB09_UART       (810U)
#define FUNC_PB10_UART       (811U)
#define FUNC_PB11_UART       (812U)
#define FUNC_PB12_UART       (813U)
#define FUNC_PB13_UART       (814U)
#define FUNC_PB14_UART       (815U)
#define FUNC_PB15_UART       (816U)
#define FUNC_PB16_UART       (817U)
#define FUNC_PB17_UART       (818U)
#define FUNC_PB18_UART       (819U)
#define FUNC_PB19_UART       (820U)
#define FUNC_PB20_UART       (821U)
#define FUNC_PB21_UART       (822U)
#define FUNC_PB22_UART       (823U)
#define FUNC_PB23_UART       (824U)
#define FUNC_PB24_UART       (825U)
#define FUNC_PB25_UART       (826U)
#define FUNC_PB26_UART       (827U)
#define FUNC_PB27_UART       (828U)
#define FUNC_PB28_UART       (829U)
#define FUNC_PB29_UART       (830U)
#define FUNC_PB30_UART       (831U)
#define FUNC_PB31_UART       (832U)
#define FUNC_PB00_I2C_UART   (833U)
#define FUNC_PB01_I2C_UART   (834U)
#define FUNC_PB02_I2C_UART   (835U)
#define FUNC_PB03_I2C_UART   (836U)
#define FUNC_PB04_I2C_UART   (837U)
#define FUNC_PB05_I2C_UART   (838U)
#define FUNC_PB06_I2C_UART   (839U)
#define FUNC_PB07_I2C_UART   (840U)
#define FUNC_PB08_I2C_UART   (841U)
#define FUNC_PB09_I2C_UART   (842U)
#define FUNC_PB10_I2C_UART   (843U)
#define FUNC_PB11_I2C_UART   (844U)
#define FUNC_PB12_I2C_UART   (845U)
#define FUNC_PB13_I2C_UART   (846U)
#define FUNC_PB14_I2C_UART   (847U)
#define FUNC_PB15_I2C_UART   (848U)
#define FUNC_PB16_I2C_UART   (849U)
#define FUNC_PB17_I2C_UART   (850U)
#define FUNC_PB18_I2C_UART   (851U)
#define FUNC_PB19_I2C_UART   (852U)
#define FUNC_PB20_I2C_UART   (853U)
#define FUNC_PB21_I2C_UART   (854U)
#define FUNC_PB22_I2C_UART   (855U)
#define FUNC_PB23_I2C_UART   (856U)
#define FUNC_PB24_I2C_UART   (857U)
#define FUNC_PB25_I2C_UART   (858U)
#define FUNC_PB26_I2C_UART   (859U)
#define FUNC_PB27_I2C_UART   (860U)
#define FUNC_PB28_I2C_UART   (861U)
#define FUNC_PB29_I2C_UART   (862U)
#define FUNC_PB30_I2C_UART   (863U)
#define FUNC_PB31_I2C_UART   (864U)
#define FUNC_PIN_FUNC_MAX    (865U)

#if 0
/** pin function */
typedef enum pin_function {
    PIN_FUNC_UNDEF,
    /** MPI1_CLK */
    MPI1_CLK,
    /** MPI1_CLKB */
    MPI1_CLKB,
    /** MPI1_CS */
    MPI1_CS,
    /** MPI1_DM */
    MPI1_DM,
    /** MPI1_DQS */
    MPI1_DQS,
    /** MPI1_DQSDM */
    MPI1_DQSDM,
    /** MPI1_DQSDM0 */
    MPI1_DQSDM0,
    /** MPI1_DQSDM1 */
    MPI1_DQSDM1,
    /** MPI1_DIO0 */
    MPI1_DIO0,
    /** MPI1_DIO1 */
    MPI1_DIO1,
    /** MPI1_DIO2 */
    MPI1_DIO2,
    /** MPI1_DIO3 */
    MPI1_DIO3,
    /** MPI1_DIO4 */
    MPI1_DIO4,
    /** MPI1_DIO5 */
    MPI1_DIO5,
    /** MPI1_DIO6 */
    MPI1_DIO6,
    /** MPI1_DIO7 */
    MPI1_DIO7,
    /** MPI1_DIO8 */
    MPI1_DIO8,
    /** MPI1_DIO9 */
    MPI1_DIO9,
    /** MPI1_DIO10 */
    MPI1_DIO10,
    /** MPI1_DIO11 */
    MPI1_DIO11,
    /** MPI1_DIO12 */
    MPI1_DIO12,
    /** MPI1_DIO13 */
    MPI1_DIO13,
    /** MPI1_DIO14 */
    MPI1_DIO14,
    /** MPI1_DIO15 */
    MPI1_DIO15,
    /** MPI2_CLK */
    MPI2_CLK,
    /** MPI2_CLKB */
    MPI2_CLKB,
    /** MPI2_CS */
    MPI2_CS,
    /** MPI2_DM */
    MPI2_DM,
    /** MPI2_DQS */
    MPI2_DQS,
    /** MPI2_DQSDM */
    MPI2_DQSDM,
    /** MPI2_DQSDM0 */
    MPI2_DQSDM0,
    /** MPI2_DQSDM1 */
    MPI2_DQSDM1,
    /** MPI2_DIO0 */
    MPI2_DIO0,
    /** MPI2_DIO1 */
    MPI2_DIO1,
    /** MPI2_DIO2 */
    MPI2_DIO2,
    /** MPI2_DIO3 */
    MPI2_DIO3,
    /** MPI2_DIO4 */
    MPI2_DIO4,
    /** MPI2_DIO5 */
    MPI2_DIO5,
    /** MPI2_DIO6 */
    MPI2_DIO6,
    /** MPI2_DIO7 */
    MPI2_DIO7,
    /** MPI2_DIO8 */
    MPI2_DIO8,
    /** MPI2_DIO9 */
    MPI2_DIO9,
    /** MPI2_DIO10 */
    MPI2_DIO10,
    /** MPI2_DIO11 */
    MPI2_DIO11,
    /** MPI2_DIO12 */
    MPI2_DIO12,
    /** MPI2_DIO13 */
    MPI2_DIO13,
    /** MPI2_DIO14 */
    MPI2_DIO14,
    /** MPI2_DIO15 */
    MPI2_DIO15,
    /** MPI3_CLK */
    MPI3_CLK,
    /** MPI3_CS */
    MPI3_CS,
    /** MPI3_DQS */
    MPI3_DQS,
    /** MPI3_DIO0 */
    MPI3_DIO0,
    /** MPI3_DIO1 */
    MPI3_DIO1,
    /** MPI3_DIO2 */
    MPI3_DIO2,
    /** MPI3_DIO3 */
    MPI3_DIO3,
    /** MPI3_DIO4 */
    MPI3_DIO4,
    /** MPI3_DIO5 */
    MPI3_DIO5,
    /** MPI3_DIO6 */
    MPI3_DIO6,
    /** MPI3_DIO7 */
    MPI3_DIO7,
    /** MPI4_CLK */
    MPI4_CLK,
    /** MPI4_CS */
    MPI4_CS,
    /** MPI4_DQS */
    MPI4_DQS,
    /** MPI4_DIO0 */
    MPI4_DIO0,
    /** MPI4_DIO1 */
    MPI4_DIO1,
    /** MPI4_DIO2 */
    MPI4_DIO2,
    /** MPI4_DIO3 */
    MPI4_DIO3,
    /** MPI4_DIO4 */
    MPI4_DIO4,
    /** MPI4_DIO5 */
    MPI4_DIO5,
    /** MPI4_DIO6 */
    MPI4_DIO6,
    /** MPI4_DIO7 */
    MPI4_DIO7,
    /** MPI5_CLK */
    MPI5_CLK,
    /** MPI5_CS */
    MPI5_CS,
    /** MPI5_DQS */
    MPI5_DQS,
    /** MPI5_DIO0 */
    MPI5_DIO0,
    /** MPI5_DIO1 */
    MPI5_DIO1,
    /** MPI5_DIO2 */
    MPI5_DIO2,
    /** MPI5_DIO3 */
    MPI5_DIO3,
    /** MPI5_DIO4 */
    MPI5_DIO4,
    /** MPI5_DIO5 */
    MPI5_DIO5,
    /** MPI5_DIO6 */
    MPI5_DIO6,
    /** MPI5_DIO7 */
    MPI5_DIO7,
    /** GPIO_A0 */
    GPIO_A0,
    /** GPIO_A1 */
    GPIO_A1,
    /** GPIO_A2 */
    GPIO_A2,
    /** GPIO_A3 */
    GPIO_A3,
    /** GPIO_A4 */
    GPIO_A4,
    /** GPIO_A5 */
    GPIO_A5,
    /** GPIO_A6 */
    GPIO_A6,
    /** GPIO_A7 */
    GPIO_A7,
    /** GPIO_A8 */
    GPIO_A8,
    /** GPIO_A9 */
    GPIO_A9,
    /** GPIO_A10 */
    GPIO_A10,
    /** GPIO_A11 */
    GPIO_A11,
    /** GPIO_A12 */
    GPIO_A12,
    /** GPIO_A13 */
    GPIO_A13,
    /** GPIO_A14 */
    GPIO_A14,
    /** GPIO_A15 */
    GPIO_A15,
    /** GPIO_A16 */
    GPIO_A16,
    /** GPIO_A17 */
    GPIO_A17,
    /** GPIO_A18 */
    GPIO_A18,
    /** GPIO_A19 */
    GPIO_A19,
    /** GPIO_A20 */
    GPIO_A20,
    /** GPIO_A21 */
    GPIO_A21,
    /** GPIO_A22 */
    GPIO_A22,
    /** GPIO_A23 */
    GPIO_A23,
    /** GPIO_A24 */
    GPIO_A24,
    /** GPIO_A25 */
    GPIO_A25,
    /** GPIO_A26 */
    GPIO_A26,
    /** GPIO_A27 */
    GPIO_A27,
    /** GPIO_A28 */
    GPIO_A28,
    /** GPIO_A29 */
    GPIO_A29,
    /** GPIO_A30 */
    GPIO_A30,
    /** GPIO_A31 */
    GPIO_A31,
    /** GPIO_A32 */
    GPIO_A32,
    /** GPIO_A33 */
    GPIO_A33,
    /** GPIO_A34 */
    GPIO_A34,
    /** GPIO_A35 */
    GPIO_A35,
    /** GPIO_A36 */
    GPIO_A36,
    /** GPIO_A37 */
    GPIO_A37,
    /** GPIO_A38 */
    GPIO_A38,
    /** GPIO_A39 */
    GPIO_A39,
    /** GPIO_A40 */
    GPIO_A40,
    /** GPIO_A41 */
    GPIO_A41,
    /** GPIO_A42 */
    GPIO_A42,
    /** GPIO_A43 */
    GPIO_A43,
    /** GPIO_A44 */
    GPIO_A44,
    /** GPIO_A45 */
    GPIO_A45,
    /** GPIO_A46 */
    GPIO_A46,
    /** GPIO_A47 */
    GPIO_A47,
    /** GPIO_A48 */
    GPIO_A48,
    /** GPIO_A49 */
    GPIO_A49,
    /** GPIO_A50 */
    GPIO_A50,
    /** GPIO_A51 */
    GPIO_A51,
    /** GPIO_A52 */
    GPIO_A52,
    /** GPIO_A53 */
    GPIO_A53,
    /** GPIO_A54 */
    GPIO_A54,
    /** GPIO_A55 */
    GPIO_A55,
    /** GPIO_A56 */
    GPIO_A56,
    /** GPIO_A57 */
    GPIO_A57,
    /** GPIO_A58 */
    GPIO_A58,
    /** GPIO_A59 */
    GPIO_A59,
    /** GPIO_A60 */
    GPIO_A60,
    /** GPIO_A61 */
    GPIO_A61,
    /** GPIO_A62 */
    GPIO_A62,
    /** GPIO_A63 */
    GPIO_A63,
    /** GPIO_A64 */
    GPIO_A64,
    /** GPIO_A65 */
    GPIO_A65,
    /** GPIO_A66 */
    GPIO_A66,
    /** GPIO_A67 */
    GPIO_A67,
    /** GPIO_A68 */
    GPIO_A68,
    /** GPIO_A69 */
    GPIO_A69,
    /** GPIO_A70 */
    GPIO_A70,
    /** GPIO_A71 */
    GPIO_A71,
    /** GPIO_A72 */
    GPIO_A72,
    /** GPIO_A73 */
    GPIO_A73,
    /** GPIO_A74 */
    GPIO_A74,
    /** GPIO_A75 */
    GPIO_A75,
    /** GPIO_A76 */
    GPIO_A76,
    /** GPIO_A77 */
    GPIO_A77,
    /** GPIO_A78 */
    GPIO_A78,
    /** GPIO_A79 */
    GPIO_A79,
    /** GPIO_A80 */
    GPIO_A80,
    /** GPIO_A81 */
    GPIO_A81,
    /** GPIO_A82 */
    GPIO_A82,
    /** GPIO_A83 */
    GPIO_A83,
    /** GPIO_A84 */
    GPIO_A84,
    /** GPIO_A85 */
    GPIO_A85,
    /** GPIO_A86 */
    GPIO_A86,
    /** GPIO_A87 */
    GPIO_A87,
    /** GPIO_A88 */
    GPIO_A88,
    /** GPIO_A89 */
    GPIO_A89,
    /** GPIO_A90 */
    GPIO_A90,
    /** GPIO_A91 */
    GPIO_A91,
    /** GPIO_A92 */
    GPIO_A92,
    /** GPIO_A93 */
    GPIO_A93,
    /** GPIO_A94 */
    GPIO_A94,
    /** GPIO_A95 */
    GPIO_A95,
    /** GPIO_B0 */
    GPIO_B0,
    /** GPIO_B1 */
    GPIO_B1,
    /** GPIO_B2 */
    GPIO_B2,
    /** GPIO_B3 */
    GPIO_B3,
    /** GPIO_B4 */
    GPIO_B4,
    /** GPIO_B5 */
    GPIO_B5,
    /** GPIO_B6 */
    GPIO_B6,
    /** GPIO_B7 */
    GPIO_B7,
    /** GPIO_B8 */
    GPIO_B8,
    /** GPIO_B9 */
    GPIO_B9,
    /** GPIO_B10 */
    GPIO_B10,
    /** GPIO_B11 */
    GPIO_B11,
    /** GPIO_B12 */
    GPIO_B12,
    /** GPIO_B13 */
    GPIO_B13,
    /** GPIO_B14 */
    GPIO_B14,
    /** GPIO_B15 */
    GPIO_B15,
    /** GPIO_B16 */
    GPIO_B16,
    /** GPIO_B17 */
    GPIO_B17,
    /** GPIO_B18 */
    GPIO_B18,
    /** GPIO_B19 */
    GPIO_B19,
    /** GPIO_B20 */
    GPIO_B20,
    /** GPIO_B21 */
    GPIO_B21,
    /** GPIO_B22 */
    GPIO_B22,
    /** GPIO_B23 */
    GPIO_B23,
    /** GPIO_B24 */
    GPIO_B24,
    /** GPIO_B25 */
    GPIO_B25,
    /** GPIO_B26 */
    GPIO_B26,
    /** GPIO_B27 */
    GPIO_B27,
    /** GPIO_B28 */
    GPIO_B28,
    /** GPIO_B29 */
    GPIO_B29,
    /** GPIO_B30 */
    GPIO_B30,
    /** GPIO_B31 */
    GPIO_B31,
    /** GPIO_B32 */
    GPIO_B32,
    /** GPIO_B33 */
    GPIO_B33,
    /** GPIO_B34 */
    GPIO_B34,
    /** GPIO_B35 */
    GPIO_B35,
    /** GPIO_B36 */
    GPIO_B36,
    /** GPIO_B37 */
    GPIO_B37,
    /** GPIO_B38 */
    GPIO_B38,
    /** GPIO_B39 */
    GPIO_B39,
    /** GPIO_B40 */
    GPIO_B40,
    /** GPIO_B41 */
    GPIO_B41,
    /** GPIO_B42 */
    GPIO_B42,
    /** GPIO_B43 */
    GPIO_B43,
    /** GPIO_B44 */
    GPIO_B44,
    /** GPIO_B45 */
    GPIO_B45,
    /** GPIO_B46 */
    GPIO_B46,
    /** GPIO_B47 */
    GPIO_B47,
    /** GPIO_B48 */
    GPIO_B48,
    /** GPIO_B49 */
    GPIO_B49,
    /** GPIO_B50 */
    GPIO_B50,
    /** GPIO_B51 */
    GPIO_B51,
    /** GPIO_B52 */
    GPIO_B52,
    /** GPIO_B53 */
    GPIO_B53,
    /** GPIO_B54 */
    GPIO_B54,
    /** GPIO_B55 */
    GPIO_B55,
    /** GPIO_B56 */
    GPIO_B56,
    /** GPIO_B57 */
    GPIO_B57,
    /** GPIO_B58 */
    GPIO_B58,
    /** GPIO_B59 */
    GPIO_B59,
    /** GPIO_B60 */
    GPIO_B60,
    /** GPIO_B61 */
    GPIO_B61,
    /** GPIO_B62 */
    GPIO_B62,
    /** GPIO_B63 */
    GPIO_B63,
    /** SAIO_D0 */
    SAIO_D0,
    /** SAIO_D1 */
    SAIO_D1,
    /** SAIO_D2 */
    SAIO_D2,
    /** SAIO_D3 */
    SAIO_D3,
    /** SAIO_D4 */
    SAIO_D4,
    /** SAIO_D5 */
    SAIO_D5,
    /** SAIO_D6 */
    SAIO_D6,
    /** SAIO_D7 */
    SAIO_D7,
    /** SAIO_D8 */
    SAIO_D8,
    /** SAIO_D9 */
    SAIO_D9,
    /** SAIO_D10 */
    SAIO_D10,
    /** SAIO_D11 */
    SAIO_D11,
    /** SAIO_D12 */
    SAIO_D12,
    /** SAIO_D13 */
    SAIO_D13,
    /** SAIO_D14 */
    SAIO_D14,
    /** SAIO_D15 */
    SAIO_D15,
    /** SAIO_D16 */
    SAIO_D16,
    /** SAIO_D17 */
    SAIO_D17,
    /** SAIO_D18 */
    SAIO_D18,
    /** SAIO_D19 */
    SAIO_D19,
    /** SBIO_D0 */
    SBIO_D0,
    /** SBIO_D1 */
    SBIO_D1,
    /** SBIO_D2 */
    SBIO_D2,
    /** SBIO_D3 */
    SBIO_D3,
    /** SBIO_D4 */
    SBIO_D4,
    /** SBIO_D5 */
    SBIO_D5,
    /** SBIO_D6 */
    SBIO_D6,
    /** SBIO_D7 */
    SBIO_D7,
    /** SBIO_D8 */
    SBIO_D8,
    /** SBIO_D9 */
    SBIO_D9,
    /** SBIO_D10 */
    SBIO_D10,
    /** SBIO_D11 */
    SBIO_D11,
    /** SBIO_D12 */
    SBIO_D12,
    /** SBIO_D13 */
    SBIO_D13,
    /** SBIO_D14 */
    SBIO_D14,
    /** SBIO_D15 */
    SBIO_D15,
    /** SBIO_D16 */
    SBIO_D16,
    /** SBIO_D17 */
    SBIO_D17,
    /** SBIO_D18 */
    SBIO_D18,
    /** SBIO_D19 */
    SBIO_D19,
    /** SCIO_D0 */
    SCIO_D0,
    /** SCIO_D1 */
    SCIO_D1,
    /** SCIO_D2 */
    SCIO_D2,
    /** SCIO_D3 */
    SCIO_D3,
    /** SCIO_D4 */
    SCIO_D4,
    /** SCIO_D5 */
    SCIO_D5,
    /** USART1_RXD */
    USART1_RXD,
    /** USART1_TXD */
    USART1_TXD,
    /** USART1_CTS */
    USART1_CTS,
    /** USART1_RTS */
    USART1_RTS,
    /** USART2_RXD */
    USART2_RXD,
    /** USART2_TXD */
    USART2_TXD,
    /** USART2_CTS */
    USART2_CTS,
    /** USART2_RTS */
    USART2_RTS,
    /** USART3_RXD */
    USART3_RXD,
    /** USART3_TXD */
    USART3_TXD,
    /** USART3_CTS */
    USART3_CTS,
    /** USART3_RTS */
    USART3_RTS,
    /** USART4_RXD */
    USART4_RXD,
    /** USART4_TXD */
    USART4_TXD,
    /** USART4_CTS */
    USART4_CTS,
    /** USART4_RTS */
    USART4_RTS,
    /** USART5_RXD */
    USART5_RXD,
    /** USART5_TXD */
    USART5_TXD,
    /** USART5_CTS */
    USART5_CTS,
    /** USART5_RTS */
    USART5_RTS,
    /** USART6_RXD */
    USART6_RXD,
    /** USART6_TXD */
    USART6_TXD,
    /** USART6_CTS */
    USART6_CTS,
    /** USART6_RTS */
    USART6_RTS,
    /** I2C1_SCL */
    I2C1_SCL,
    /** I2C1_SDA */
    I2C1_SDA,
    /** I2C2_SCL */
    I2C2_SCL,
    /** I2C2_SDA */
    I2C2_SDA,
    /** I2C3_SCL */
    I2C3_SCL,
    /** I2C3_SDA */
    I2C3_SDA,
    /** I2C4_SCL */
    I2C4_SCL,
    /** I2C4_SDA */
    I2C4_SDA,
    /** I2C5_SCL */
    I2C5_SCL,
    /** I2C5_SDA */
    I2C5_SDA,
    /** I2C6_SCL */
    I2C6_SCL,
    /** I2C6_SDA */
    I2C6_SDA,
    /** I2C7_SCL */
    I2C7_SCL,
    /** I2C7_SDA */
    I2C7_SDA,
    /** SPI1_CLK */
    SPI1_CLK,
    /** SPI1_CS */
    SPI1_CS,
    /** SPI1_DI */
    SPI1_DI,
    /** SPI1_DO */
    SPI1_DO,
    /** SPI1_DIO */
    SPI1_DIO,
    /** SPI2_CLK */
    SPI2_CLK,
    /** SPI2_CS */
    SPI2_CS,
    /** SPI2_DI */
    SPI2_DI,
    /** SPI2_DO */
    SPI2_DO,
    /** SPI2_DIO */
    SPI2_DIO,
    /** SPI3_CLK */
    SPI3_CLK,
    /** SPI3_CS */
    SPI3_CS,
    /** SPI3_DI */
    SPI3_DI,
    /** SPI3_DO */
    SPI3_DO,
    /** SPI3_DIO */
    SPI3_DIO,
    /** SPI4_CLK */
    SPI4_CLK,
    /** SPI4_CS */
    SPI4_CS,
    /** SPI4_DI */
    SPI4_DI,
    /** SPI4_DO */
    SPI4_DO,
    /** SPI4_DIO */
    SPI4_DIO,
    /** SPI5_CLK */
    SPI5_CLK,
    /** SPI5_CS */
    SPI5_CS,
    /** SPI5_DI */
    SPI5_DI,
    /** SPI5_DO */
    SPI5_DO,
    /** SPI5_DIO */
    SPI5_DIO,
    /** LCDC1_SPI_CS */
    LCDC1_SPI_CS,
    /** LCDC1_SPI_CLK */
    LCDC1_SPI_CLK,
    /** LCDC1_SPI_DIO0 */
    LCDC1_SPI_DIO0,
    /** LCDC1_SPI_DIO1 */
    LCDC1_SPI_DIO1,
    /** LCDC1_SPI_DIO2 */
    LCDC1_SPI_DIO2,
    /** LCDC1_SPI_DIO3 */
    LCDC1_SPI_DIO3,
    /** LCDC1_SPI_RSTB */
    LCDC1_SPI_RSTB,
    /** LCDC1_SPI_TE */
    LCDC1_SPI_TE,
    /** LCDC2_SPI_CS */
    LCDC2_SPI_CS,
    /** LCDC2_SPI_CLK */
    LCDC2_SPI_CLK,
    /** LCDC2_SPI_DIO0 */
    LCDC2_SPI_DIO0,
    /** LCDC2_SPI_DIO1 */
    LCDC2_SPI_DIO1,
    /** LCDC2_SPI_DIO2 */
    LCDC2_SPI_DIO2,
    /** LCDC2_SPI_DIO3 */
    LCDC2_SPI_DIO3,
    /** LCDC2_SPI_RSTB */
    LCDC2_SPI_RSTB,
    /** LCDC2_SPI_TE */
    LCDC2_SPI_TE,
    /** LCDC1_8080_WR */
    LCDC1_8080_WR,
    /** LCDC1_8080_CS */
    LCDC1_8080_CS,
    /** LCDC1_8080_DIO0 */
    LCDC1_8080_DIO0,
    /** LCDC1_8080_DIO1 */
    LCDC1_8080_DIO1,
    /** LCDC1_8080_DIO2 */
    LCDC1_8080_DIO2,
    /** LCDC1_8080_DIO3 */
    LCDC1_8080_DIO3,
    /** LCDC1_8080_DIO4 */
    LCDC1_8080_DIO4,
    /** LCDC1_8080_DIO5 */
    LCDC1_8080_DIO5,
    /** LCDC1_8080_DIO6 */
    LCDC1_8080_DIO6,
    /** LCDC1_8080_DIO7 */
    LCDC1_8080_DIO7,
    /** LCDC1_8080_RD */
    LCDC1_8080_RD,
    /** LCDC1_8080_DC */
    LCDC1_8080_DC,
    /** LCDC1_8080_RSTB */
    LCDC1_8080_RSTB,
    /** LCDC1_8080_TE */
    LCDC1_8080_TE,
    /** LCDC1_DPI_CLK */
    LCDC1_DPI_CLK,
    /** LCDC1_DPI_DE */
    LCDC1_DPI_DE,
    /** LCDC1_DPI_SD */
    LCDC1_DPI_SD,
    /** LCDC1_DPI_CM */
    LCDC1_DPI_CM,
    /** LCDC1_DPI_HSYNC */
    LCDC1_DPI_HSYNC,
    /** LCDC1_DPI_VSYNC */
    LCDC1_DPI_VSYNC,
    /** LCDC1_DPI_R7 */
    LCDC1_DPI_R7,
    /** LCDC1_DPI_R6 */
    LCDC1_DPI_R6,
    /** LCDC1_DPI_R5 */
    LCDC1_DPI_R5,
    /** LCDC1_DPI_R4 */
    LCDC1_DPI_R4,
    /** LCDC1_DPI_R3 */
    LCDC1_DPI_R3,
    /** LCDC1_DPI_R2 */
    LCDC1_DPI_R2,
    /** LCDC1_DPI_R1 */
    LCDC1_DPI_R1,
    /** LCDC1_DPI_R0 */
    LCDC1_DPI_R0,
    /** LCDC1_DPI_G7 */
    LCDC1_DPI_G7,
    /** LCDC1_DPI_G6 */
    LCDC1_DPI_G6,
    /** LCDC1_DPI_G5 */
    LCDC1_DPI_G5,
    /** LCDC1_DPI_G4 */
    LCDC1_DPI_G4,
    /** LCDC1_DPI_G3 */
    LCDC1_DPI_G3,
    /** LCDC1_DPI_G2 */
    LCDC1_DPI_G2,
    /** LCDC1_DPI_G1 */
    LCDC1_DPI_G1,
    /** LCDC1_DPI_G0 */
    LCDC1_DPI_G0,
    /** LCDC1_DPI_B7 */
    LCDC1_DPI_B7,
    /** LCDC1_DPI_B6 */
    LCDC1_DPI_B6,
    /** LCDC1_DPI_B5 */
    LCDC1_DPI_B5,
    /** LCDC1_DPI_B4 */
    LCDC1_DPI_B4,
    /** LCDC1_DPI_B3 */
    LCDC1_DPI_B3,
    /** LCDC1_DPI_B2 */
    LCDC1_DPI_B2,
    /** LCDC1_DPI_B1 */
    LCDC1_DPI_B1,
    /** LCDC1_DPI_B0 */
    LCDC1_DPI_B0,
    /** LCDC1_JDI_SCLK */
    LCDC1_JDI_SCLK,
    /** LCDC1_JDI_SCS */
    LCDC1_JDI_SCS,
    /** LCDC1_JDI_SO */
    LCDC1_JDI_SO,
    /** LCDC1_JDI_DISP */
    LCDC1_JDI_DISP,
    /** LCDC1_JDI_EXTCOMIN */
    LCDC1_JDI_EXTCOMIN,
    /** LCDC1_JDI_XRST */
    LCDC1_JDI_XRST,
    /** LCDC1_JDI_VCK */
    LCDC1_JDI_VCK,
    /** LCDC1_JDI_VST */
    LCDC1_JDI_VST,
    /** LCDC1_JDI_ENB */
    LCDC1_JDI_ENB,
    /** LCDC1_JDI_HCK */
    LCDC1_JDI_HCK,
    /** LCDC1_JDI_HST */
    LCDC1_JDI_HST,
    /** LCDC1_JDI_R1 */
    LCDC1_JDI_R1,
    /** LCDC1_JDI_R2 */
    LCDC1_JDI_R2,
    /** LCDC1_JDI_G1 */
    LCDC1_JDI_G1,
    /** LCDC1_JDI_G2 */
    LCDC1_JDI_G2,
    /** LCDC1_JDI_B1 */
    LCDC1_JDI_B1,
    /** LCDC1_JDI_B2 */
    LCDC1_JDI_B2,
    /** LCDC1_JDI_FRP */
    LCDC1_JDI_FRP,
    /** LCDC1_JDI_XFRP */
    LCDC1_JDI_XFRP,
    /** LCDC1_JDI_VCOM */
    LCDC1_JDI_VCOM,
    /** LCDC2_JDI_SCLK */
    LCDC2_JDI_SCLK,
    /** LCDC2_JDI_SCS */
    LCDC2_JDI_SCS,
    /** LCDC2_JDI_SO */
    LCDC2_JDI_SO,
    /** LCDC2_JDI_DISP */
    LCDC2_JDI_DISP,
    /** LCDC2_JDI_EXTCOMIN */
    LCDC2_JDI_EXTCOMIN,
    /** LCDC2_JDI_XRST */
    LCDC2_JDI_XRST,
    /** LCDC2_JDI_VCK */
    LCDC2_JDI_VCK,
    /** LCDC2_JDI_VST */
    LCDC2_JDI_VST,
    /** LCDC2_JDI_ENB */
    LCDC2_JDI_ENB,
    /** LCDC2_JDI_HCK */
    LCDC2_JDI_HCK,
    /** LCDC2_JDI_HST */
    LCDC2_JDI_HST,
    /** LCDC2_JDI_R1 */
    LCDC2_JDI_R1,
    /** LCDC2_JDI_R2 */
    LCDC2_JDI_R2,
    /** LCDC2_JDI_G1 */
    LCDC2_JDI_G1,
    /** LCDC2_JDI_G2 */
    LCDC2_JDI_G2,
    /** LCDC2_JDI_B1 */
    LCDC2_JDI_B1,
    /** LCDC2_JDI_B2 */
    LCDC2_JDI_B2,
    /** LCDC2_JDI_FRP */
    LCDC2_JDI_FRP,
    /** LCDC2_JDI_XFRP */
    LCDC2_JDI_XFRP,
    /** LCDC2_JDI_VCOM */
    LCDC2_JDI_VCOM,
    /** SD1_CLK */
    SD1_CLK,
    /** SD1_CLKIN */
    SD1_CLKIN,
    /** SD1_CMD */
    SD1_CMD,
    /** SD1_DIO0 */
    SD1_DIO0,
    /** SD1_DIO1 */
    SD1_DIO1,
    /** SD1_DIO2 */
    SD1_DIO2,
    /** SD1_DIO3 */
    SD1_DIO3,
    /** SD1_DIO4 */
    SD1_DIO4,
    /** SD1_DIO5 */
    SD1_DIO5,
    /** SD1_DIO6 */
    SD1_DIO6,
    /** SD1_DIO7 */
    SD1_DIO7,
    /** SD2_CLK */
    SD2_CLK,
    /** SD2_CLKIN */
    SD2_CLKIN,
    /** SD2_CMD */
    SD2_CMD,
    /** SD2_DIO0 */
    SD2_DIO0,
    /** SD2_DIO1 */
    SD2_DIO1,
    /** SD2_DIO2 */
    SD2_DIO2,
    /** SD2_DIO3 */
    SD2_DIO3,
    /** I2S1_BCK */
    I2S1_BCK,
    /** I2S1_LRCK */
    I2S1_LRCK,
    /** I2S1_MCLK */
    I2S1_MCLK,
    /** I2S1_SDI */
    I2S1_SDI,
    /** I2S1_SDO */
    I2S1_SDO,
    /** I2S2_BCK */
    I2S2_BCK,
    /** I2S2_LRCK */
    I2S2_LRCK,
    /** I2S2_MCLK */
    I2S2_MCLK,
    /** I2S2_SDI */
    I2S2_SDI,
    /** I2S2_SDO */
    I2S2_SDO,
    /** I2S3_BCK */
    I2S3_BCK,
    /** I2S3_LRCK */
    I2S3_LRCK,
    /** I2S3_MCLK */
    I2S3_MCLK,
    /** I2S3_SDI */
    I2S3_SDI,
    /** I2S3_SDO */
    I2S3_SDO,
    /** AUD_CLK_EXT */
    AUD_CLK_EXT,
    /** PDM1_CLK */
    PDM1_CLK,
    /** PDM1_DATA */
    PDM1_DATA,
    /** PDM2_CLK */
    PDM2_CLK,
    /** PDM2_DATA */
    PDM2_DATA,
    /** GPTIM1_CH1 */
    GPTIM1_CH1,
    /** GPTIM1_CH2 */
    GPTIM1_CH2,
    /** GPTIM1_CH3 */
    GPTIM1_CH3,
    /** GPTIM1_CH4 */
    GPTIM1_CH4,
    /** GPTIM1_ETR */
    GPTIM1_ETR,
    /** GPTIM2_CH1 */
    GPTIM2_CH1,
    /** GPTIM2_CH2 */
    GPTIM2_CH2,
    /** GPTIM2_CH3 */
    GPTIM2_CH3,
    /** GPTIM2_CH4 */
    GPTIM2_CH4,
    /** GPTIM2_ETR */
    GPTIM2_ETR,
    /** GPTIM3_CH1 */
    GPTIM3_CH1,
    /** GPTIM3_CH2 */
    GPTIM3_CH2,
    /** GPTIM3_CH3 */
    GPTIM3_CH3,
    /** GPTIM3_CH4 */
    GPTIM3_CH4,
    /** GPTIM3_ETR */
    GPTIM3_ETR,
    /** GPTIM4_CH1 */
    GPTIM4_CH1,
    /** GPTIM4_CH2 */
    GPTIM4_CH2,
    /** GPTIM4_CH3 */
    GPTIM4_CH3,
    /** GPTIM4_CH4 */
    GPTIM4_CH4,
    /** GPTIM4_ETR */
    GPTIM4_ETR,
    /** GPTIM5_CH1 */
    GPTIM5_CH1,
    /** GPTIM5_CH2 */
    GPTIM5_CH2,
    /** GPTIM5_CH3 */
    GPTIM5_CH3,
    /** GPTIM5_CH4 */
    GPTIM5_CH4,
    /** GPTIM5_ETR */
    GPTIM5_ETR,
    /** ATIM1_CH1 */
    ATIM1_CH1,
    /** ATIM1_CH1N */
    ATIM1_CH1N,
    /** ATIM1_CH2 */
    ATIM1_CH2,
    /** ATIM1_CH2N */
    ATIM1_CH2N,
    /** ATIM1_CH3 */
    ATIM1_CH3,
    /** ATIM1_CH3N */
    ATIM1_CH3N,
    /** ATIM1_CH4 */
    ATIM1_CH4,
    /** ATIM1_ETR */
    ATIM1_ETR,
    /** ATIM1_BKIN */
    ATIM1_BKIN,
    /** ATIM1_BKIN2 */
    ATIM1_BKIN2,
    /** ATIM2_CH1 */
    ATIM2_CH1,
    /** ATIM2_CH1N */
    ATIM2_CH1N,
    /** ATIM2_CH2 */
    ATIM2_CH2,
    /** ATIM2_CH2N */
    ATIM2_CH2N,
    /** ATIM2_CH3 */
    ATIM2_CH3,
    /** ATIM2_CH3N */
    ATIM2_CH3N,
    /** ATIM2_CH4 */
    ATIM2_CH4,
    /** ATIM2_ETR */
    ATIM2_ETR,
    /** ATIM2_BKIN */
    ATIM2_BKIN,
    /** ATIM2_BKIN2 */
    ATIM2_BKIN2,
    /** LPTIM1_IN */
    LPTIM1_IN,
    /** LPTIM1_OUT */
    LPTIM1_OUT,
    /** LPTIM1_ETR */
    LPTIM1_ETR,
    /** LPTIM2_IN */
    LPTIM2_IN,
    /** LPTIM2_OUT */
    LPTIM2_OUT,
    /** LPTIM2_ETR */
    LPTIM2_ETR,
    /** LPTIM3_IN */
    LPTIM3_IN,
    /** LPTIM3_OUT */
    LPTIM3_OUT,
    /** LPTIM3_ETR */
    LPTIM3_ETR,
    /** LPCOMP1_OUT */
    LPCOMP1_OUT,
    /** LPCOMP2_OUT */
    LPCOMP2_OUT,
    /** SCI_RST */
    SCI_RST,
    /** SCI_CLK */
    SCI_CLK,
    /** SCI_DIO */
    SCI_DIO,
    /** CAN1_RXD */
    CAN1_RXD,
    /** CAN1_TXD */
    CAN1_TXD,
    /** CAN1_STBY */
    CAN1_STBY,
    /** CAN2_RXD */
    CAN2_RXD,
    /** CAN2_TXD */
    CAN2_TXD,
    /** CAN2_STBY */
    CAN2_STBY,
    /** SWCLK */
    SWCLK,
    /** SWDIO */
    SWDIO,
    /** TWI_CLK */
    TWI_CLK,
    /** TWI_DIO */
    TWI_DIO,
    /** BT_ACTIVE */
    BT_ACTIVE,
    /** WLAN_ACTIVE */
    WLAN_ACTIVE,
    /** BT_PRIORITY */
    BT_PRIORITY,
    /** BT_COLLISION */
    BT_COLLISION,
    /** SCAN_CLK */
    SCAN_CLK,
    /** SCAN_RSTB */
    SCAN_RSTB,
    /** SCAN_EN */
    SCAN_EN,
    /** EDT_CLK */
    EDT_CLK,
    /** EDT_UPDATE */
    EDT_UPDATE,
    /** EDT_BYPASS */
    EDT_BYPASS,
    /** EDT_CHANNEL_IN0 */
    EDT_CHANNEL_IN0,
    /** EDT_CHANNEL_IN1 */
    EDT_CHANNEL_IN1,
    /** EDT_CHANNEL_IN2 */
    EDT_CHANNEL_IN2,
    /** EDT_CHANNEL_IN3 */
    EDT_CHANNEL_IN3,
    /** EDT_CHANNEL_IN4 */
    EDT_CHANNEL_IN4,
    /** EDT_CHANNEL_IN5 */
    EDT_CHANNEL_IN5,
    /** EDT_CHANNEL_IN6 */
    EDT_CHANNEL_IN6,
    /** EDT_CHANNEL_IN7 */
    EDT_CHANNEL_IN7,
    /** EDT_CHANNEL_OUT0 */
    EDT_CHANNEL_OUT0,
    /** EDT_CHANNEL_OUT1 */
    EDT_CHANNEL_OUT1,
    /** EDT_CHANNEL_OUT2 */
    EDT_CHANNEL_OUT2,
    /** EDT_CHANNEL_OUT3 */
    EDT_CHANNEL_OUT3,
    /** EDT_CHANNEL_OUT4 */
    EDT_CHANNEL_OUT4,
    /** EDT_CHANNEL_OUT5 */
    EDT_CHANNEL_OUT5,
    /** EDT_CHANNEL_OUT6 */
    EDT_CHANNEL_OUT6,
    /** EDT_CHANNEL_OUT7 */
    EDT_CHANNEL_OUT7,
    /** BIST_CLK */
    BIST_CLK,
    /** BIST_RST */
    BIST_RST,
    /** BIST_FAIL */
    BIST_FAIL,
    /** BIST_DONE */
    BIST_DONE,
    /** DBG_DO0 */
    DBG_DO0,
    /** DBG_DO1 */
    DBG_DO1,
    /** DBG_DO2 */
    DBG_DO2,
    /** DBG_DO3 */
    DBG_DO3,
    /** DBG_DO4 */
    DBG_DO4,
    /** DBG_DO5 */
    DBG_DO5,
    /** DBG_DO6 */
    DBG_DO6,
    /** DBG_DO7 */
    DBG_DO7,
    /** DBG_DO8 */
    DBG_DO8,
    /** DBG_DO9 */
    DBG_DO9,
    /** DBG_DO10 */
    DBG_DO10,
    /** DBG_DO11 */
    DBG_DO11,
    /** DBG_DO12 */
    DBG_DO12,
    /** DBG_DO13 */
    DBG_DO13,
    /** DBG_DO14 */
    DBG_DO14,
    /** DBG_DO15 */
    DBG_DO15,
    /** DBG_CLK */
    DBG_CLK,
    /** EXT_S_TX_EN */
    EXT_S_TX_EN,
    /** EXT_S_RX_EN */
    EXT_S_RX_EN,
    /** EXT_S_LE_2M */
    EXT_S_LE_2M,
    /** EXT_S_LE_MODE */
    EXT_S_LE_MODE,
    /** EXT_S_TX_BIT0 */
    EXT_S_TX_BIT0,
    /** EXT_S_TX_BIT1 */
    EXT_S_TX_BIT1,
    /** EXT_S_TX_BIT2 */
    EXT_S_TX_BIT2,
    /** EXT_S_TX_FLAG */
    EXT_S_TX_FLAG,
    /** EXT_S_EDR2_MODE */
    EXT_S_EDR2_MODE,
    /** EXT_S_EDR3_MODE */
    EXT_S_EDR3_MODE,
    /** EXT_S_BR_LAST_BIT */
    EXT_S_BR_LAST_BIT,
    /** EXT_S_EDR_LAST_BIT */
    EXT_S_EDR_LAST_BIT,
    /** EXT_S_EDR_BIT_FLAG */
    EXT_S_EDR_BIT_FLAG,
    /** EXT_S_RAMP_UP_IND */
    EXT_S_RAMP_UP_IND,
    /** EXT_S_EDR_EN */
    EXT_S_EDR_EN,
    /** EXT_S_SYNC_CLK */
    EXT_S_SYNC_CLK,
    /** EXT_S_SYNC_DAT */
    EXT_S_SYNC_DAT,
    /** EXT_S_SCLK */
    EXT_S_SCLK,
    /** EXT_S_SDO */
    EXT_S_SDO,
    /** EXT_S_RX_BIT0 */
    EXT_S_RX_BIT0,
    /** EXT_S_RX_BIT1 */
    EXT_S_RX_BIT1,
    /** EXT_S_RX_BIT2 */
    EXT_S_RX_BIT2,
    /** EXT_S_RX_FLAG */
    EXT_S_RX_FLAG,
    /** PA00_TIM */
    PA00_TIM,
    /** PA01_TIM */
    PA01_TIM,
    /** PA02_TIM */
    PA02_TIM,
    /** PA03_TIM */
    PA03_TIM,
    /** PA04_TIM */
    PA04_TIM,
    /** PA05_TIM */
    PA05_TIM,
    /** PA06_TIM */
    PA06_TIM,
    /** PA07_TIM */
    PA07_TIM,
    /** PA08_TIM */
    PA08_TIM,
    /** PA09_TIM */
    PA09_TIM,
    /** PA10_TIM */
    PA10_TIM,
    /** PA11_TIM */
    PA11_TIM,
    /** PA12_TIM */
    PA12_TIM,
    /** PA13_TIM */
    PA13_TIM,
    /** PA14_TIM */
    PA14_TIM,
    /** PA15_TIM */
    PA15_TIM,
    /** PA16_TIM */
    PA16_TIM,
    /** PA17_TIM */
    PA17_TIM,
    /** PA18_TIM */
    PA18_TIM,
    /** PA19_TIM */
    PA19_TIM,
    /** PA20_TIM */
    PA20_TIM,
    /** PA21_TIM */
    PA21_TIM,
    /** PA22_TIM */
    PA22_TIM,
    /** PA23_TIM */
    PA23_TIM,
    /** PA24_TIM */
    PA24_TIM,
    /** PA25_TIM */
    PA25_TIM,
    /** PA26_TIM */
    PA26_TIM,
    /** PA27_TIM */
    PA27_TIM,
    /** PA28_TIM */
    PA28_TIM,
    /** PA29_TIM */
    PA29_TIM,
    /** PA30_TIM */
    PA30_TIM,
    /** PA31_TIM */
    PA31_TIM,
    /** PA32_TIM */
    PA32_TIM,
    /** PA33_TIM */
    PA33_TIM,
    /** PA34_TIM */
    PA34_TIM,
    /** PA35_TIM */
    PA35_TIM,
    /** PA36_TIM */
    PA36_TIM,
    /** PA37_TIM */
    PA37_TIM,
    /** PA38_TIM */
    PA38_TIM,
    /** PA39_TIM */
    PA39_TIM,
    /** PA40_TIM */
    PA40_TIM,
    /** PA41_TIM */
    PA41_TIM,
    /** PA42_TIM */
    PA42_TIM,
    /** PA43_TIM */
    PA43_TIM,
    /** PA44_TIM */
    PA44_TIM,
    /** PA45_TIM */
    PA45_TIM,
    /** PA46_TIM */
    PA46_TIM,
    /** PA47_TIM */
    PA47_TIM,
    /** PA48_TIM */
    PA48_TIM,
    /** PA49_TIM */
    PA49_TIM,
    /** PA50_TIM */
    PA50_TIM,
    /** PA51_TIM */
    PA51_TIM,
    /** PA52_TIM */
    PA52_TIM,
    /** PA53_TIM */
    PA53_TIM,
    /** PA54_TIM */
    PA54_TIM,
    /** PA55_TIM */
    PA55_TIM,
    /** PA56_TIM */
    PA56_TIM,
    /** PA57_TIM */
    PA57_TIM,
    /** PA58_TIM */
    PA58_TIM,
    /** PA59_TIM */
    PA59_TIM,
    /** PA60_TIM */
    PA60_TIM,
    /** PA61_TIM */
    PA61_TIM,
    /** PA62_TIM */
    PA62_TIM,
    /** PA63_TIM */
    PA63_TIM,
    /** PA64_TIM */
    PA64_TIM,
    /** PA65_TIM */
    PA65_TIM,
    /** PA66_TIM */
    PA66_TIM,
    /** PA67_TIM */
    PA67_TIM,
    /** PA68_TIM */
    PA68_TIM,
    /** PA69_TIM */
    PA69_TIM,
    /** PA70_TIM */
    PA70_TIM,
    /** PA71_TIM */
    PA71_TIM,
    /** PA72_TIM */
    PA72_TIM,
    /** PA73_TIM */
    PA73_TIM,
    /** PA74_TIM */
    PA74_TIM,
    /** PA75_TIM */
    PA75_TIM,
    /** PA76_TIM */
    PA76_TIM,
    /** PA77_TIM */
    PA77_TIM,
    /** PA78_TIM */
    PA78_TIM,
    /** PA00_I2C_UART */
    PA00_I2C_UART,
    /** PA01_I2C_UART */
    PA01_I2C_UART,
    /** PA02_I2C_UART */
    PA02_I2C_UART,
    /** PA03_I2C_UART */
    PA03_I2C_UART,
    /** PA04_I2C_UART */
    PA04_I2C_UART,
    /** PA05_I2C_UART */
    PA05_I2C_UART,
    /** PA06_I2C_UART */
    PA06_I2C_UART,
    /** PA07_I2C_UART */
    PA07_I2C_UART,
    /** PA08_I2C_UART */
    PA08_I2C_UART,
    /** PA09_I2C_UART */
    PA09_I2C_UART,
    /** PA10_I2C_UART */
    PA10_I2C_UART,
    /** PA11_I2C_UART */
    PA11_I2C_UART,
    /** PA12_I2C_UART */
    PA12_I2C_UART,
    /** PA13_I2C_UART */
    PA13_I2C_UART,
    /** PA14_I2C_UART */
    PA14_I2C_UART,
    /** PA15_I2C_UART */
    PA15_I2C_UART,
    /** PA16_I2C_UART */
    PA16_I2C_UART,
    /** PA17_I2C_UART */
    PA17_I2C_UART,
    /** PA18_I2C_UART */
    PA18_I2C_UART,
    /** PA19_I2C_UART */
    PA19_I2C_UART,
    /** PA20_I2C_UART */
    PA20_I2C_UART,
    /** PA21_I2C_UART */
    PA21_I2C_UART,
    /** PA22_I2C_UART */
    PA22_I2C_UART,
    /** PA23_I2C_UART */
    PA23_I2C_UART,
    /** PA24_I2C_UART */
    PA24_I2C_UART,
    /** PA25_I2C_UART */
    PA25_I2C_UART,
    /** PA26_I2C_UART */
    PA26_I2C_UART,
    /** PA27_I2C_UART */
    PA27_I2C_UART,
    /** PA28_I2C_UART */
    PA28_I2C_UART,
    /** PA29_I2C_UART */
    PA29_I2C_UART,
    /** PA30_I2C_UART */
    PA30_I2C_UART,
    /** PA31_I2C_UART */
    PA31_I2C_UART,
    /** PA32_I2C_UART */
    PA32_I2C_UART,
    /** PA33_I2C_UART */
    PA33_I2C_UART,
    /** PA34_I2C_UART */
    PA34_I2C_UART,
    /** PA35_I2C_UART */
    PA35_I2C_UART,
    /** PA36_I2C_UART */
    PA36_I2C_UART,
    /** PA37_I2C_UART */
    PA37_I2C_UART,
    /** PA38_I2C_UART */
    PA38_I2C_UART,
    /** PA39_I2C_UART */
    PA39_I2C_UART,
    /** PA40_I2C_UART */
    PA40_I2C_UART,
    /** PA41_I2C_UART */
    PA41_I2C_UART,
    /** PA42_I2C_UART */
    PA42_I2C_UART,
    /** PA43_I2C_UART */
    PA43_I2C_UART,
    /** PA44_I2C_UART */
    PA44_I2C_UART,
    /** PA45_I2C_UART */
    PA45_I2C_UART,
    /** PA46_I2C_UART */
    PA46_I2C_UART,
    /** PA47_I2C_UART */
    PA47_I2C_UART,
    /** PA48_I2C_UART */
    PA48_I2C_UART,
    /** PA49_I2C_UART */
    PA49_I2C_UART,
    /** PA50_I2C_UART */
    PA50_I2C_UART,
    /** PA51_I2C_UART */
    PA51_I2C_UART,
    /** PA52_I2C_UART */
    PA52_I2C_UART,
    /** PA53_I2C_UART */
    PA53_I2C_UART,
    /** PA54_I2C_UART */
    PA54_I2C_UART,
    /** PA55_I2C_UART */
    PA55_I2C_UART,
    /** PA56_I2C_UART */
    PA56_I2C_UART,
    /** PA57_I2C_UART */
    PA57_I2C_UART,
    /** PA58_I2C_UART */
    PA58_I2C_UART,
    /** PA59_I2C_UART */
    PA59_I2C_UART,
    /** PA60_I2C_UART */
    PA60_I2C_UART,
    /** PA61_I2C_UART */
    PA61_I2C_UART,
    /** PA62_I2C_UART */
    PA62_I2C_UART,
    /** PA63_I2C_UART */
    PA63_I2C_UART,
    /** PA64_I2C_UART */
    PA64_I2C_UART,
    /** PA65_I2C_UART */
    PA65_I2C_UART,
    /** PA66_I2C_UART */
    PA66_I2C_UART,
    /** PA67_I2C_UART */
    PA67_I2C_UART,
    /** PA68_I2C_UART */
    PA68_I2C_UART,
    /** PA69_I2C_UART */
    PA69_I2C_UART,
    /** PA70_I2C_UART */
    PA70_I2C_UART,
    /** PA71_I2C_UART */
    PA71_I2C_UART,
    /** PA72_I2C_UART */
    PA72_I2C_UART,
    /** PA73_I2C_UART */
    PA73_I2C_UART,
    /** PA74_I2C_UART */
    PA74_I2C_UART,
    /** PA75_I2C_UART */
    PA75_I2C_UART,
    /** PA76_I2C_UART */
    PA76_I2C_UART,
    /** PA77_I2C_UART */
    PA77_I2C_UART,
    /** PA78_I2C_UART */
    PA78_I2C_UART,
    /** PB00_TIM */
    PB00_TIM,
    /** PB01_TIM */
    PB01_TIM,
    /** PB02_TIM */
    PB02_TIM,
    /** PB03_TIM */
    PB03_TIM,
    /** PB04_TIM */
    PB04_TIM,
    /** PB05_TIM */
    PB05_TIM,
    /** PB06_TIM */
    PB06_TIM,
    /** PB07_TIM */
    PB07_TIM,
    /** PB08_TIM */
    PB08_TIM,
    /** PB09_TIM */
    PB09_TIM,
    /** PB10_TIM */
    PB10_TIM,
    /** PB11_TIM */
    PB11_TIM,
    /** PB12_TIM */
    PB12_TIM,
    /** PB13_TIM */
    PB13_TIM,
    /** PB14_TIM */
    PB14_TIM,
    /** PB15_TIM */
    PB15_TIM,
    /** PB16_TIM */
    PB16_TIM,
    /** PB17_TIM */
    PB17_TIM,
    /** PB18_TIM */
    PB18_TIM,
    /** PB19_TIM */
    PB19_TIM,
    /** PB20_TIM */
    PB20_TIM,
    /** PB21_TIM */
    PB21_TIM,
    /** PB22_TIM */
    PB22_TIM,
    /** PB23_TIM */
    PB23_TIM,
    /** PB24_TIM */
    PB24_TIM,
    /** PB25_TIM */
    PB25_TIM,
    /** PB26_TIM */
    PB26_TIM,
    /** PB27_TIM */
    PB27_TIM,
    /** PB28_TIM */
    PB28_TIM,
    /** PB29_TIM */
    PB29_TIM,
    /** PB30_TIM */
    PB30_TIM,
    /** PB31_TIM */
    PB31_TIM,
    /** PB00_I2C_UART */
    PB00_I2C_UART,
    /** PB01_I2C_UART */
    PB01_I2C_UART,
    /** PB02_I2C_UART */
    PB02_I2C_UART,
    /** PB03_I2C_UART */
    PB03_I2C_UART,
    /** PB04_I2C_UART */
    PB04_I2C_UART,
    /** PB05_I2C_UART */
    PB05_I2C_UART,
    /** PB06_I2C_UART */
    PB06_I2C_UART,
    /** PB07_I2C_UART */
    PB07_I2C_UART,
    /** PB08_I2C_UART */
    PB08_I2C_UART,
    /** PB09_I2C_UART */
    PB09_I2C_UART,
    /** PB10_I2C_UART */
    PB10_I2C_UART,
    /** PB11_I2C_UART */
    PB11_I2C_UART,
    /** PB12_I2C_UART */
    PB12_I2C_UART,
    /** PB13_I2C_UART */
    PB13_I2C_UART,
    /** PB14_I2C_UART */
    PB14_I2C_UART,
    /** PB15_I2C_UART */
    PB15_I2C_UART,
    /** PB16_I2C_UART */
    PB16_I2C_UART,
    /** PB17_I2C_UART */
    PB17_I2C_UART,
    /** PB18_I2C_UART */
    PB18_I2C_UART,
    /** PB19_I2C_UART */
    PB19_I2C_UART,
    /** PB20_I2C_UART */
    PB20_I2C_UART,
    /** PB21_I2C_UART */
    PB21_I2C_UART,
    /** PB22_I2C_UART */
    PB22_I2C_UART,
    /** PB23_I2C_UART */
    PB23_I2C_UART,
    /** PB24_I2C_UART */
    PB24_I2C_UART,
    /** PB25_I2C_UART */
    PB25_I2C_UART,
    /** PB26_I2C_UART */
    PB26_I2C_UART,
    /** PB27_I2C_UART */
    PB27_I2C_UART,
    /** PB28_I2C_UART */
    PB28_I2C_UART,
    /** PB29_I2C_UART */
    PB29_I2C_UART,
    /** PB30_I2C_UART */
    PB30_I2C_UART,
    /** PB31_I2C_UART */
    PB31_I2C_UART,
    /** PBR_PWR_REQ */
    PBR_PWR_REQ,
    /** PBR_GPO */
    PBR_GPO,
    /** PBR_CLK_LP */
    PBR_CLK_LP,
    /** PBR_LPTIM3_OUT */
    PBR_LPTIM3_OUT,
    /** PBR_LPTIM3_OUT_BAR */
    PBR_LPTIM3_OUT_BAR,
    PIN_FUNC_MAX,
} pin_function;
#endif

#define PIN_PAD_SA00 (1U)
#define PIN_PAD_SA01 (2U)
#define PIN_PAD_SA02 (3U)
#define PIN_PAD_SA03 (4U)
#define PIN_PAD_SA04 (5U)
#define PIN_PAD_SA05 (6U)
#define PIN_PAD_SA06 (7U)
#define PIN_PAD_SA07 (8U)
#define PIN_PAD_SA08 (9U)
#define PIN_PAD_SA09 (10U)
#define PIN_PAD_SA10 (11U)
#define PIN_PAD_SA11 (12U)
#define PIN_PAD_SA12 (13U)

#define PIN_PAD_PA00 (14U)
#define PIN_PAD_PA01 (15U)
#define PIN_PAD_PA02 (16U)
#define PIN_PAD_PA03 (17U)
#define PIN_PAD_PA04 (18U)
#define PIN_PAD_PA05 (19U)
#define PIN_PAD_PA06 (20U)
#define PIN_PAD_PA07 (21U)
#define PIN_PAD_PA08 (22U)
#define PIN_PAD_PA09 (23U)
#define PIN_PAD_PA10 (24U)
#define PIN_PAD_PA11 (25U)
#define PIN_PAD_PA12 (26U)
#define PIN_PAD_PA13 (27U)
#define PIN_PAD_PA14 (28U)
#define PIN_PAD_PA15 (29U)
#define PIN_PAD_PA16 (30U)
#define PIN_PAD_PA17 (31U)
#define PIN_PAD_PA18 (32U)
#define PIN_PAD_PA19 (33U)
#define PIN_PAD_PA20 (34U)
#define PIN_PAD_PA21 (35U)
#define PIN_PAD_PA22 (36U)
#define PIN_PAD_PA23 (37U)
#define PIN_PAD_PA24 (38U)
#define PIN_PAD_PA25 (39U)
#define PIN_PAD_PA26 (40U)
#define PIN_PAD_PA27 (41U)
#define PIN_PAD_PA28 (42U)
#define PIN_PAD_PA29 (43U)
#define PIN_PAD_PA30 (44U)
#define PIN_PAD_PA31 (45U)
#define PIN_PAD_PA32 (46U)
#define PIN_PAD_PA33 (47U)
#define PIN_PAD_PA34 (48U)
#define PIN_PAD_PA35 (49U)
#define PIN_PAD_PA36 (50U)
#define PIN_PAD_PA37 (51U)
#define PIN_PAD_PA38 (52U)
#define PIN_PAD_PA39 (53U)
#define PIN_PAD_PA40 (54U)
#define PIN_PAD_PA41 (55U)
#define PIN_PAD_PA42 (56U)
#define PIN_PAD_PA43 (57U)
#define PIN_PAD_PA44 (58U)

#if 0
/** HCPU pin pad */
typedef enum
{
    PIN_PAD_UNDEF_H,
    /** PAD_SA00 */
    PAD_SA00,
    /** PAD_SA01 */
    PAD_SA01,
    /** PAD_SA02 */
    PAD_SA02,
    /** PAD_SA03 */
    PAD_SA03,
    /** PAD_SA04 */
    PAD_SA04,
    /** PAD_SA05 */
    PAD_SA05,
    /** PAD_SA06 */
    PAD_SA06,
    /** PAD_SA07 */
    PAD_SA07,
    /** PAD_SA08 */
    PAD_SA08,
    /** PAD_SA09 */
    PAD_SA09,
    /** PAD_SA10 */
    PAD_SA10,
    /** PAD_SA11 */
    PAD_SA11,
    /** PAD_SA12 */
    PAD_SA12,
    /** PAD_SB00 */
    PAD_SB00,
    /** PAD_SB01 */
    PAD_SB01,
    /** PAD_SB02 */
    PAD_SB02,
    /** PAD_SB03 */
    PAD_SB03,
    /** PAD_SB04 */
    PAD_SB04,
    /** PAD_SB05 */
    PAD_SB05,
    /** PAD_SB06 */
    PAD_SB06,
    /** PAD_SB07 */
    PAD_SB07,
    /** PAD_SB08 */
    PAD_SB08,
    /** PAD_SB09 */
    PAD_SB09,
    /** PAD_SB10 */
    PAD_SB10,
    /** PAD_SB11 */
    PAD_SB11,
    /** PAD_SB12 */
    PAD_SB12,
    /** PAD_PA00 */
    PAD_PA00,
    /** PAD_PA01 */
    PAD_PA01,
    /** PAD_PA02 */
    PAD_PA02,
    /** PAD_PA03 */
    PAD_PA03,
    /** PAD_PA04 */
    PAD_PA04,
    /** PAD_PA05 */
    PAD_PA05,
    /** PAD_PA06 */
    PAD_PA06,
    /** PAD_PA07 */
    PAD_PA07,
    /** PAD_PA08 */
    PAD_PA08,
    /** PAD_PA09 */
    PAD_PA09,
    /** PAD_PA10 */
    PAD_PA10,
    /** PAD_PA11 */
    PAD_PA11,
    /** PAD_PA12 */
    PAD_PA12,
    /** PAD_PA13 */
    PAD_PA13,
    /** PAD_PA14 */
    PAD_PA14,
    /** PAD_PA15 */
    PAD_PA15,
    /** PAD_PA16 */
    PAD_PA16,
    /** PAD_PA17 */
    PAD_PA17,
    /** PAD_PA18 */
    PAD_PA18,
    /** PAD_PA19 */
    PAD_PA19,
    /** PAD_PA20 */
    PAD_PA20,
    /** PAD_PA21 */
    PAD_PA21,
    /** PAD_PA22 */
    PAD_PA22,
    /** PAD_PA23 */
    PAD_PA23,
    /** PAD_PA24 */
    PAD_PA24,
    /** PAD_PA25 */
    PAD_PA25,
    /** PAD_PA26 */
    PAD_PA26,
    /** PAD_PA27 */
    PAD_PA27,
    /** PAD_PA28 */
    PAD_PA28,
    /** PAD_PA29 */
    PAD_PA29,
    /** PAD_PA30 */
    PAD_PA30,
    /** PAD_PA31 */
    PAD_PA31,
    /** PAD_PA32 */
    PAD_PA32,
    /** PAD_PA33 */
    PAD_PA33,
    /** PAD_PA34 */
    PAD_PA34,
    /** PAD_PA35 */
    PAD_PA35,
    /** PAD_PA36 */
    PAD_PA36,
    /** PAD_PA37 */
    PAD_PA37,
    /** PAD_PA38 */
    PAD_PA38,
    /** PAD_PA39 */
    PAD_PA39,
    /** PAD_PA40 */
    PAD_PA40,
    /** PAD_PA41 */
    PAD_PA41,
    /** PAD_PA42 */
    PAD_PA42,
    /** PAD_PA43 */
    PAD_PA43,
    /** PAD_PA44 */
    PAD_PA44,
    /** PAD_PA45 */
    PAD_PA45,
    /** PAD_PA46 */
    PAD_PA46,
    /** PAD_PA47 */
    PAD_PA47,
    /** PAD_PA48 */
    PAD_PA48,
    /** PAD_PA49 */
    PAD_PA49,
    /** PAD_PA50 */
    PAD_PA50,
    /** PAD_PA51 */
    PAD_PA51,
    /** PAD_PA52 */
    PAD_PA52,
    /** PAD_PA53 */
    PAD_PA53,
    /** PAD_PA54 */
    PAD_PA54,
    /** PAD_PA55 */
    PAD_PA55,
    /** PAD_PA56 */
    PAD_PA56,
    /** PAD_PA57 */
    PAD_PA57,
    /** PAD_PA58 */
    PAD_PA58,
    /** PAD_PA59 */
    PAD_PA59,
    /** PAD_PA60 */
    PAD_PA60,
    /** PAD_PA61 */
    PAD_PA61,
    /** PAD_PA62 */
    PAD_PA62,
    /** PAD_PA63 */
    PAD_PA63,
    /** PAD_PA64 */
    PAD_PA64,
    /** PAD_PA65 */
    PAD_PA65,
    /** PAD_PA66 */
    PAD_PA66,
    /** PAD_PA67 */
    PAD_PA67,
    /** PAD_PA68 */
    PAD_PA68,
    /** PAD_PA69 */
    PAD_PA69,
    /** PAD_PA70 */
    PAD_PA70,
    /** PAD_PA71 */
    PAD_PA71,
    /** PAD_PA72 */
    PAD_PA72,
    /** PAD_PA73 */
    PAD_PA73,
    /** PAD_PA74 */
    PAD_PA74,
    /** PAD_PA75 */
    PAD_PA75,
    /** PAD_PA76 */
    PAD_PA76,
    /** PAD_PA77 */
    PAD_PA77,
    /** PAD_PA78 */
    PAD_PA78,
    PIN_PAD_MAX_H,
} pin_pad_hcpu;
#endif
#endif /* _ZEPHYR_INCLUDE_DT_BINDINGS_PINCTRL_SFLB32_PINCTRL_H_ */