# S3term
I started making this firmware for one of the [CYD clones](https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display) but i ran into problems with limited memory and improperly wired io. Switching to an S3 clone allowed access to 8MB of octal spi memory and the abiliy to load and execute code in memory, which is required for the program-loading feature i will be adding. this also means it is not backwards-compatible with Wroom ESPs.

due to the hardware change it lacks features such as traditional bluetooth.

## Hardware
all of the pinouts and data can be found [here](https://www.lcdwiki.com/2.8inch_ESP32-S3_Display).

i got mine from [aliexpress](https://www.aliexpress.us/item/3256809690313727.html?spm=a2g0o.detail.pcDetailTopMoreOtherSeller.61.32dblYSalYSa4x&gps-id=pcDetailTopMoreOtherSeller&scm=1007.40050.354490.0&scm_id=1007.40050.354490.0&scm-url=1007.40050.354490.0&pvid=f732ad9b-2a4c-4958-9c58-d01313c5446e&_t=gps-id:pcDetailTopMoreOtherSeller,scm-url:1007.40050.354490.0,pvid:f732ad9b-2a4c-4958-9c58-d01313c5446e,tpp_buckets:668%232846%238114%231999&isseo=y&pdp_ext_f=%7B%22order%22%3A%22171%22%2C%22eval%22%3A%221%22%2C%22sceneId%22%3A%2230050%22%2C%22fromPage%22%3A%22recommend%22%7D&pdp_npi=6%40dis%21USD%2113.47%2112.12%21%21%2192.27%2183.04%21%402101e83017755174018806393e628b%2112000050451385865%21rec%21US%21%21ABXZ%211%210%21n_tag%3A-29910%3Bd%3Add3db5f%3Bm03_new_user%3A-29895&utparam-url=scene%3ApcDetailTopMoreOtherSeller%7Cquery_from%3A%7Cx_object_id%3A1005009876628479%7C_p_origin_prod%3A)

if you wanna port this to a different dev board most things you'll need to change are in 'pins.h'. this project uses ArduinoGFX so graphics should be compatible with most screens.

!!!if you use the battery connector it has to be a protected cell to prevent over-discharge!!!

## Installation
its not finished yet but if you wanna test it or make changes install PIO-cli, cd into the directory with 'platformio.ini' and run 'pio run --target upload'.
im sure you could flash it with the Platformio desktop application but i havent tried so im not sure.

## Features
as of now its just a menu with some test actions when the corners are touched.

planned features:<br>
settings menu<br>
app launcher<br>
custom menu models<br>
debug terminal<br>
LoRa radio capabilities<br>
16-bit audio DAC<br>
[CardKb](https://shop.m5stack.com/products/cardkb-mini-keyboard-programmable-unit-v1-1-mega8a?variant=43165484482817) support<br>
circuitpython interperator<br>
[maybe] wii nunchuck support<br>
