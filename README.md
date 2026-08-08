# OVERBoard
This is my attempt at creating a custom keyboard with several unique features, this has a layer system that I have modified to work with specific tasks on my pc, I also have a 2.8 in screen to display custom text, ui, and macros. There is a full 78 led matrix, dual pi pico system, and 3 rotary encoders that interface in this system.   
# Key Features   
Full TKL Keyboard Matrix   
4 Layer Keyboard System   
3 Encoders Interfacing with the Layer System   
78 Led Matrix system   
320 x 240 2.8 inch display   
Custom UI and layer switching menus   
Computer interface and data transmission   
Custom 5A power system   

## Onshape-link:
https://cad.onshape.com/documents/a6bd6c4e9013194f1dc31777/w/de360b55982ee6c60ca7c4d4/e/a374dba059f4ceb7d8e6600d?renderMode=0&uiState=6a4a7855afac9a027952f82f 

# Flashing      
Flashing is done through two steps, compiling the C qmk file through QMK MSYS to compile to a uf2 file, which then can be flashed to the pi pico through holding the bootsel button and plugging it in to the usb power. Then just upload the new uf2 file to the pi pico. To flash the pi pico 2 for the display, you have to download the entire folder of the custom c++, and then through a terminal of your choice compile it. (I use vs code and i got it to work through there, idk about others). Then upload the second uf2 file to the pi pico 2 by holding the bootsel button and uploading it there.

# BOM   
78 [3 Pin Mechanical Keyboard Switches   ](https://www.amazon.com/Leezmark-Mechanical-Dustproof-Replacement-Keyboards/dp/B0GV78B48N/ref=mp_s_a_1_20_sspa?crid=2GGAVKPX5GKH&dib=eyJ2IjoiMSJ9.BS9ZW8A40QZK6iI4UmdZkYcVp812RDtM8dzqQtxJq5kz5jddC0aGCLYpUDj6oWZM4geYAz7LL5dJKQJ_sMRCqYbuT9Zwzy20VnrTvVNVI-2PMGM8y_OT_gXPSKltVj0ZCmtBrzLAvtF8hVyPpS-bcG8HSGX4meJ7BWVw4GwyFBtzq-VV4k_-OB3_U29mYmabBNX5P_2u1xLUz0WsYM_SZg.sOaHXiIPD6Bd4c6RHFdcsiI9AAYZXd1oFGZit3XfvzE&dib_tag=se&keywords=mechanical+keyboard+switches&qid=1786102391&sprefix=mecha%2Caps%2C1667&sr=8-20-spons&xpid=P4xuzyhmO1Kis&sp_csd=d2lkZ2V0TmFtZT1zcF9waG9uZV9zZWFyY2hfbXRm&psc=1)   
78 [SK6812 Mini-E LEDs](https://www.amazon.com/Lizusidtsy-Similar-Individually-Addressable-500076361/dp/B0D62PYX62/ref=mp_s_a_1_10?crid=1HXPOB1FA28BI&dib=eyJ2IjoiMSJ9.9VtPip6eaOO1-XFGgh2XxRcv7goQ3zQpYu2U5s9L9nSHVgE9buEYKNyEW3iah_ciC9jxtcFWsezkLg6mPwawYLvC0YwcBautoxVQw8uHIajIIKaw2BAEOz0msTKg2i1JiFDcOfpwOktIFD5m-rM-sLH5aurg7jONQpTc9ztb7qjGY4VW4UKlHhBSvXDKLMnpFN1p0uSk9QlHmR1fMhQoKQ.cp7zFL1gJURH3RVmt4PrTOWDThkTRaVYkx8k7CsSdDU&dib_tag=se&keywords=sk6812+mini+e&qid=1786102738&s=industrial&sprefix=sk6812+mini+e%2Cindustrial%2C227&sr=1-10-catcorr)   
3 [EC11 Rotary encoders](https://www.amazon.com/CGNRONEAU-Potentiometer-Raspberry-Electronics-Projects/dp/B0G48Z8B9Q/ref=mp_s_a_1_5?crid=SJZ3ZTB60ZB5&dib=eyJ2IjoiMSJ9.DXj00Da7o69UiffMrM5wQRPYTBTu96F7xG_REVVFTXyDDE7Ct_VRsisag9rFMKgkTnHD1maKyGOHqHwwsa9QOm4nJbuxf-u1h8I8Xeu_QS-_GGyZhZ7IW7rUedH8wyPUQpJnUpBYRTrw7qkoa3L6uI7fxGQ1JdWoYiTZq1MJnh7YbKwp_SVgYWuv54q8JgQ_uJAa0EScvo-vtg_HxxVShA.oFRLtfeS884kGRJ9817n1MkEJusgqgWJDlI8D6AScFo&dib_tag=se&keywords=ec11+rotary+encoder&qid=1786102850&s=industrial&sprefix=ec11+rotary+encoder%2Cindustrial%2C296&sr=1-5)    
1 [Keycap Set](https://www.amazon.com/Womier-Doubleshot-Universal-Compatiability-Switches/dp/B0DD3MFZJH/ref=mp_s_a_1_4?dib=eyJ2IjoiMSJ9.NYb-M_oBXZ4sYXBFeumxLCGVNsY9r-6v4MP0X_NiII59u2l-eoBS-fSIwKjgQw8UQnKp5aItpglhW1_vmJ5Zi3Ai9TdxAWYqoLRUdImCShzhl38JPSy1eJCwtC9gqwE5WcnlIVPYZwyoVEbIaEuOxTBP47_ipk5BJsu7sIIcEQwtiRsUoIT2AKQ4hwcLJanAgVfd3swCPsz1cHzkkB3fEA.LHY6OJX_2Vt0jXq0Am2Od0HAyrY-O1Iw68TDGDFU8LQ&dib_tag=se&keywords=keycap+set&qid=1786102952&sr=8-4)   
1 [Stabilizer Set](https://www.amazon.com/DUROCK-Stabilizers-Translucent-Keyboard-Mechanical/dp/B0B2RVN19F/ref=mp_s_a_1_1?crid=RUCGVW5PCSL7&dib=eyJ2IjoiMSJ9.FUE_jABwKLA1OASEMhZRJdxEw5T6Pmde5A4peNgmaHbFq5e1Nyw0ducx_W87F-YdPvY6Z0F0Ws9Z5KWRT10otnbc7i3mqQ-KSsT8q0_UoKFDrMQOU2Zr7UFsQVD8SH_3jzvns1ANBC4ikHp7kZKjsS9mrpaVKSuOX6QgBT75oK6L6rT38cDrAPZf1bMy2eiDNbRMvr3UK6Jnu7D304s7ww.Ds4MVNaTUXEreelnZ5y9dkQEI_1UVwucidZDuxVlDSo&dib_tag=se&keywords=keyboard+stabilizer+pcb+mount&qid=1786103068&sprefix=keyboard+stabilizer+pcb+moun%2Cpc%2C281&sr=8-1)   
10 [0.1uF SMD 0805 Capacitors](https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL21B104KBCNNNC/3886661)   
2 [10uF SMD 1206 Capacitors](https://www.digikey.com/en/products/detail/taiyo-yuden/TMK316BJ106ML-T/1172143)   
83 [Through Hole Diodes](https://www.digikey.com/en/products/detail/onsemi/1N4148TR/458811)   
1 [Raspberry Pi Pico](https://www.digikey.com/en/products/detail/raspberry-pi/SC0915/13624793)   
1 [Raspberry Pi Pico 2](https://www.digikey.com/en/products/detail/raspberry-pi/SC1631/24627136)   
1 [SN74HCT245PWR](https://www.digikey.com/en/products/detail/texas-instruments/SN74HCT245PWR/376998)   
1 [Mini 560 5A 5V](https://www.amazon.com/ACEIRMC-Efficiency-Converter-Regulator-Stabilized/dp/B0C98GN9R5/ref=mp_s_a_1_4?crid=2AVG7EVJEY2B9&dib=eyJ2IjoiMSJ9.YQJnYbrVm2KfCwo1WAsOv_9mCXY0p27qXY_bAWcHnAztXAalke-6x_LLhC_8PmYHInSFxohDrh9t3UeH3i8bvUFj-epQ0_xXJwlrhhlWOhZJfog3TIgcDjFTwO7dwkMsRUWsBu6tSt_Lye0NUieFGLgw9ekInTt2RbwoX9bJ0JOObYWOKjC2M1PCHkkIN_Ke.J03En0j60RIf0zi2gOz474K4xhu8YiPPLa1dOAJTqoU&dib_tag=se&keywords=mini+560+5v+5a&qid=1786103755&sprefix=mi%2Cpc%2C4329&sr=8-4)   
1 [Adafruit 5807 Power Evaluation Board](https://www.digikey.com/en/products/detail/adafruit-industries-llc/5807/21839778)   
1 [2.8 in 320 x 240 SPI Serial TFT display](https://www.amazon.com/DIANN-ILI9341-Display-320x240-Screen/dp/B0BNQBKFCT/ref=mp_s_a_1_4?crid=1IO0JMISFCIW5&dib=eyJ2IjoiMSJ9.QdQv9Z60xKItFJyKtGDGVEe0E5DZHOpvSyDlzSsJM0ahxq3n0oBPRCWegDN5Bh4kMcEsYOjRE9r_6PQ-nRDFi45yabmboblZpYIfpVL-1wZ9Gbc-wRBgY9Q3zt3W4nQNGskA3h3qFBMzfNfbmmOG4S9Yv8aLMXAZH_x-N28DwhMUSRzU2xY8tLeu3uxt2kHptwfZuykGqU6NKyFsdJm3gw.irWclV9rp7JxQy7JeD-LQJ3wXUPrGnMFIF87TexXEg0&dib_tag=se&keywords=2.8+in+spi+display+color&qid=1786105121&s=industrial&sprefix=2.8+in+spi+display+color%2Cindustrial%2C196&sr=1-4)   
2 [PTS810_SJM_250](https://www.digikey.com/en/products/detail/c-k/PTS810SJK250SMTR-LFS/4176611)   
2 [4.7k SMD 0805 resistors](https://www.digikey.com/en/products/detail/panasonic-industry/ERA-6AEB472V/1465765)    
10 [10k SMD 0805 resistors](https://www.digikey.com/en/products/detail/stackpole-electronics-inc/RMCF0805FT10K0/1760676)   
## Extra Parts not part of BOM
9 [M3 Heat set inserts](https://www.amazon.com/HANGLIFE-Heat-Set-Threaded-Printing-Components/dp/B0CS6VZYL8/ref=mp_s_a_1_2_sspa?crid=2B6EZ44CM5F8W&dib=eyJ2IjoiMSJ9.64CwhAq2F4wt2J7X2RWpxsbGQNoHV8siDt0bl6JQWF52xU_4RhH0jdpfO7SRVfnWZU2jv3CI10a2JeWKff2m2wFIr10td08-ZNDs7jlZM_gW5mSgs-W56Qb0sIpuTAgPvamIXJbOre0ZmTZ6kXSKiIbGKsS7vC-VFf2Imqp2yVl_mDHaTy5djVOZQ_dIL6f3OuER50SkQsIQripMtAXk4A.KM8dXGX0d71WWG7ur53YMH8J9nQ2REom7eKTVHaXpUI&dib_tag=se&keywords=m3+heat+set+inserts&qid=1786105506&s=industrial&sprefix=m3+heat+s%2Cindustrial%2C246&sr=1-2-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9waG9uZV9zZWFyY2hfYXRm&psc=1)   
9 [M3 Screws](https://www.amazon.com/Fgruh-750PCS-Assortment-Washers-Assorted/dp/B0FGV5FCBN/ref=mp_s_a_1_1_sspa?crid=1ZGG85P77CJCY&dib=eyJ2IjoiMSJ9.cPekTjkEYdRojQiPp36UK-D0OriKRZ1Tcz-iYae4l8YfNDd_5vroqMqjPyDoD8r98dxg69F8Q4x7A4Qg04ZpZkq3-5Vz_8pzyy0ST4oyfjEEufYmdOm-INr8fJD5TDph9qhOa-j-fmcB0ADX9T1tIyiP6yaLBkyUwThoKVBjPId_kiXSb0qIrofmAIKtf7pJRZK1cPMjvmaWqAiZ1AKcZg.GNyAzvliKQY6RL9mJRsNCAE3UinRfEleG_EmtBRQXtc&dib_tag=se&keywords=m3+screws&qid=1786105661&s=industrial&sprefix=m3+screws%2Cindustrial%2C256&sr=1-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9waG9uZV9zZWFyY2hfYXRm&psc=1)   
2 [M2.5 Heat Set Inserts](https://www.amazon.com/HANGLIFE-Heat-Set-Threaded-Printing-Components/dp/B0CS6YVJYD/ref=mp_s_a_1_2_sspa?crid=2B6EZ44CM5F8W&dib=eyJ2IjoiMSJ9.64CwhAq2F4wt2J7X2RWpxsbGQNoHV8siDt0bl6JQWF52xU_4RhH0jdpfO7SRVfnWZU2jv3CI10a2JeWKff2m2wFIr10td08-ZNDs7jlZM_gW5mSgs-W56Qb0sIpuTAgPvamIXJbOre0ZmTZ6kXSKiIbGKsS7vC-VFf2Imqp2yVl_mDHaTy5djVOZQ_dIL6f3OuER50SkQsIQripMtAXk4A.KM8dXGX0d71WWG7ur53YMH8J9nQ2REom7eKTVHaXpUI&dib_tag=se&keywords=m3%2Bheat%2Bset%2Binserts&qid=1786105506&s=industrial&sprefix=m3%2Bheat%2Bs%2Cindustrial%2C246&sr=1-2-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9waG9uZV9zZWFyY2hfYXRm&psc=1&th=1)   
2 [M2.5 Screws](https://www.amazon.com/Fgruh-750PCS-Assortment-Washers-Assorted/dp/B0FG2BYJSR/ref=mp_s_a_1_1_sspa?crid=1ZGG85P77CJCY&dib=eyJ2IjoiMSJ9.cPekTjkEYdRojQiPp36UK-D0OriKRZ1Tcz-iYae4l8YfNDd_5vroqMqjPyDoD8r98dxg69F8Q4x7A4Qg04ZpZkq3-5Vz_8pzyy0ST4oyfjEEufYmdOm-INr8fJD5TDph9qhOa-j-fmcB0ADX9T1tIyiP6yaLBkyUwThoKVBjPId_kiXSb0qIrofmAIKtf7pJRZK1cPMjvmaWqAiZ1AKcZg.GNyAzvliKQY6RL9mJRsNCAE3UinRfEleG_EmtBRQXtc&dib_tag=se&keywords=m3%2Bscrews&qid=1786105661&s=industrial&sprefix=m3%2Bscrews%2Cindustrial%2C256&sr=1-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9waG9uZV9zZWFyY2hfYXRm&psc=1&th=1)   
1 [1Kg Matte Black Filament](https://www.amazon.com/ELEGOO-Filament-Dimensional-Accuracy-Carboard/dp/B0CFV3WF7P/ref=mp_s_a_1_1_sspa?crid=2WGHGADYDSPZ3&dib=eyJ2IjoiMSJ9.jj4FdZs0k5Gj9BMVFw2sIqMRLoQnKg6Dh9C_efasYCNLHC9B4MPcdiQZZ9ZXBsrlR_gga4llJi5TY_AL7se-jTgKuxSOclNDDB5CvK38oBG-ydVc6MiEftwGY9kheukIrHDEPPKRb3bsytmUJS91ZC5HKMM_KCdLlz8CiN8cHiQ8tEZizCX_oA0306VRSqZExDdBiODIV9xqZQAQjvHG-Q.TCRhgAn-7mqXjFZFVEeZ7ere4YNhtVbXsh61Izosbp4&dib_tag=se&keywords=matte+black+pla&qid=1786105829&s=industrial&sprefix=matte+black+pla%2Cindustrial%2C248&sr=1-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9waG9uZV9zZWFyY2hfYXRm&psc=1)   
1 Custom Pcb    
## BOM as CSV Format    
[BOM.csv](https://github.com/Nikhil-Krishnamurthy/OVERBoard/blob/main/BOM.csv)     

# Full Render:    
<img width="1461" height="663" alt="image" src="https://github.com/user-attachments/assets/057a3dc0-9586-4152-a7f4-11bf910e8b55" />


# Schematic:   
<img width="1460" height="486" alt="image" src="https://github.com/user-attachments/assets/248533e1-3a99-4dfb-975f-4928a19c0cac" />
<img width="993" height="638" alt="image" src="https://github.com/user-attachments/assets/fae9c9ba-902a-40fc-bbde-526d5c62177d" />
<img width="1808" height="707" alt="image" src="https://github.com/user-attachments/assets/6381c7dc-2fac-4012-b84f-b1e7646ad149" />
<img width="1495" height="557" alt="image" src="https://github.com/user-attachments/assets/752ad3e1-cdba-420e-9648-0243d6767b6b" />
<img width="1895" height="1347" alt="image" src="https://github.com/user-attachments/assets/b87516bf-3a16-4fd3-814b-ae81b4431bc1" />

# PCB:
<img width="2085" height="777" alt="image" src="https://github.com/user-attachments/assets/22abf3f7-aad8-46b6-84cc-de4dc688b701" />
<img width="2084" height="760" alt="image" src="https://github.com/user-attachments/assets/0b2ae1bd-d65d-444e-a3b4-1056811a891a" />

# CAD:
<img width="1345" height="522" alt="image" src="https://github.com/user-attachments/assets/bea1ad18-e2e1-4c06-b54d-8852fae5b384" />

   
