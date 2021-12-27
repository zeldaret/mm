# Useful conversions

This article contains some useful conversion tables. Beware that we will omit the `0x` prefix on hex numbers: it will be evident from context which base is intended.

- [Degrees and hex/binary angles](#degrees-and-hex-binary-angles)
    * [Small angles](#small-angles)
    * [Larger angles](#larger-angles)
- [Round decimal numbers in hex](#round-decimal-numbers-in-hex)
    * [Small](#small)
    * [Medium](#medium)
    * [Large](#large)
- [Extra large](#extra-large)
- [Shifts/powers of 2 in dec and hex](#shifts-powers-of-2-in-dec-and-hex)

## Degrees and hex/binary angles

Conversion of degrees to binary angles in the two common ways, that give different answers. Table is produced using this script:

```bash
$ printf "%s\t%s\t%s\n" "d" "d * 2^16/360" "2^16/360 * d" ; for i in {0..360..5} ; do printf "%d\t%X\t\t%X\n" "$i" $(( "$i" * 0x10000 / 360 )) $(( 0x10000 / 360 * "$i" )) ; done
```

### Small angles

| `d`   | `d * 2^16/360` | `2^16/360 * d` |
| ----: | -------------: | -------------: |
| 0     | 0              | 0              |
| 1     | B6             | B6             |
| 2     | 16C            | 16C            |
| 3     | 222            | 222            |
| 4     | 2D8            | 2D8            |
| 5     | 38E            | 38E            |
| 6     | 444            | 444            |
| 7     | 4FA            | 4FA            |
| 8     | 5B0            | 5B0            |
| 9     | 666            | 666            |
| 10    | 71C            | 71C            |
| 11    | 7D2            | 7D2            |
| 12    | 888            | 888            |
| 13    | 93E            | 93E            |
| 14    | 9F4            | 9F4            |
| 15    | AAA            | AAA            |
| 16    | B60            | B60            |
| 17    | C16            | C16            |
| 18    | CCC            | CCC            |
| 19    | D82            | D82            |
| 20    | E38            | E38            |
| 21    | EEE            | EEE            |
| 22    | FA4            | FA4            |
| 23    | 105B           | 105A           |
| 24    | 1111           | 1110           |
| 25    | 11C7           | 11C6           |
| 26    | 127D           | 127C           |
| 27    | 1333           | 1332           |
| 28    | 13E9           | 13E8           |
| 29    | 149F           | 149E           |
| 30    | 1555           | 1554           |

### Larger angles

| `d`    | `d * 2^16/360` | `2^16/360 * d` |
| -----: | -------------: | -------------: |
| 0      | 0              | 0              |
| 5      | 38E            | 38E            |
| 10     | 71C            | 71C            |
| 15     | AAA            | AAA            |
| 20     | E38            | E38            |
| 25     | 11C7           | 11C6           |
| 30     | 1555           | 1554           |
| 35     | 18E3           | 18E2           |
| 40     | 1C71           | 1C70           |
| 45     | 2000           | 1FFE           |
| 50     | 238E           | 238C           |
| 55     | 271C           | 271A           |
| 60     | 2AAA           | 2AA8           |
| 65     | 2E38           | 2E36           |
| 70     | 31C7           | 31C4           |
| 75     | 3555           | 3552           |
| 80     | 38E3           | 38E0           |
| 85     | 3C71           | 3C6E           |
| 90     | 4000           | 3FFC           |
| 95     | 438E           | 438A           |
| 100    | 471C           | 4718           |
| 105    | 4AAA           | 4AA6           |
| 110    | 4E38           | 4E34           |
| 115    | 51C7           | 51C2           |
| 120    | 5555           | 5550           |
| 125    | 58E3           | 58DE           |
| 130    | 5C71           | 5C6C           |
| 135    | 6000           | 5FFA           |
| 140    | 638E           | 6388           |
| 145    | 671C           | 6716           |
| 150    | 6AAA           | 6AA4           |
| 155    | 6E38           | 6E32           |
| 160    | 71C7           | 71C0           |
| 165    | 7555           | 754E           |
| 170    | 78E3           | 78DC           |
| 175    | 7C71           | 7C6A           |
| 180    | 8000           | 7FF8           |
| 185    | 838E           | 8386           |
| 190    | 871C           | 8714           |
| 195    | 8AAA           | 8AA2           |
| 200    | 8E38           | 8E30           |
| 205    | 91C7           | 91BE           |
| 210    | 9555           | 954C           |
| 215    | 98E3           | 98DA           |
| 220    | 9C71           | 9C68           |
| 225    | A000           | 9FF6           |
| 230    | A38E           | A384           |
| 235    | A71C           | A712           |
| 240    | AAAA           | AAA0           |
| 245    | AE38           | AE2E           |
| 250    | B1C7           | B1BC           |
| 255    | B555           | B54A           |
| 260    | B8E3           | B8D8           |
| 265    | BC71           | BC66           |
| 270    | C000           | BFF4           |
| 275    | C38E           | C382           |
| 280    | C71C           | C710           |
| 285    | CAAA           | CA9E           |
| 290    | CE38           | CE2C           |
| 295    | D1C7           | D1BA           |
| 300    | D555           | D548           |
| 305    | D8E3           | D8D6           |
| 310    | DC71           | DC64           |
| 315    | E000           | DFF2           |
| 320    | E38E           | E380           |
| 325    | E71C           | E70E           |
| 330    | EAAA           | EA9C           |
| 335    | EE38           | EE2A           |
| 340    | F1C7           | F1B8           |
| 345    | F555           | F546           |
| 350    | F8E3           | F8D4           |
| 355    | FC71           | FC62           |
| 360    | 10000          | FFF0           |

Similarly for small angles with a smaller increment:



## Round decimal numbers in hex

```bash
printf "%s\t%s\n" "dec" "hex" ; for i in {0..100..5} ; do printf "%d\t%X\n" "$i" "$i" ; done
```

### Small

| dec    | hex |
| -----: | --: |
| 0      | 0   |
| 5      | 5   |
| 10     | A   |
| 15     | F   |
| 20     | 14  |
| 25     | 19  |
| 30     | 1E  |
| 35     | 23  |
| 40     | 28  |
| 45     | 2D  |
| 50     | 32  |
| 55     | 37  |
| 60     | 3C  |
| 65     | 41  |
| 70     | 46  |
| 75     | 4B  |
| 80     | 50  |
| 85     | 55  |
| 90     | 5A  |
| 95     | 5F  |
| 100    | 64  |


### Medium

| dec    | hex  |
| -----: | ---: |
| 100    | 64   |
| 150    | 96   |
| 200    | C8   |
| 250    | FA   |
| 300    | 12C  |
| 350    | 15E  |
| 400    | 190  |
| 450    | 1C2  |
| 500    | 1F4  |
| 550    | 226  |
| 600    | 258  |
| 650    | 28A  |
| 700    | 2BC  |
| 750    | 2EE  |
| 800    | 320  |
| 850    | 352  |
| 900    | 384  |
| 950    | 3B6  |
| 1000   | 3E8  |


### Large

| dec    | hex   |
| -----: | ----: |
| 1000   | 3E8   |
| 1500   | 5DC   |
| 2000   | 7D0   |
| 2500   | 9C4   |
| 3000   | BB8   |
| 3500   | DAC   |
| 4000   | FA0   |
| 4500   | 1194  |
| 5000   | 1388  |
| 5500   | 157C  |
| 6000   | 1770  |
| 6500   | 1964  |
| 7000   | 1B58  |
| 7500   | 1D4C  |
| 8000   | 1F40  |
| 8500   | 2134  |
| 9000   | 2328  |
| 9500   | 251C  |
| 10000  | 2710  |


## Extra large
| dec    | hex   |
| -----: | ----: |
| 10000  | 2710  |
| 11000  | 2AF8  |
| 12000  | 2EE0  |
| 13000  | 32C8  |
| 14000  | 36B0  |
| 15000  | 3A98  |
| 16000  | 3E80  |
| 17000  | 4268  |
| 18000  | 4650  |
| 19000  | 4A38  |
| 20000  | 4E20  |
| 21000  | 5208  |
| 22000  | 55F0  |
| 23000  | 59D8  |
| 24000  | 5DC0  |
| 25000  | 61A8  |
| 26000  | 6590  |
| 27000  | 6978  |
| 28000  | 6D60  |
| 29000  | 7148  |
| 30000  | 7530  |

## Shifts/powers of 2 in dec and hex

```bash
$ printf "%s\t%s\t%s\n" "n" "1 << n (hex)" "1 << n (dec)" ; for i in {0..15..1} ; do printf "%d\t%X\t\t%d\n" "$i" $(( 1 << "$i" )) $(( 1 << "$i" )) ; done
```
`1 << n` is the same as `2^n`.

| `n`    | `1 << n` (hex) | `1 << n` (dec) |
| -----: | -------------: | -------------: |
| 0      | 1              | 1              |
| 1      | 2              | 2              |
| 2      | 4              | 4              |
| 3      | 8              | 8              |
| 4      | 10             | 16             |
| 5      | 20             | 32             |
| 6      | 40             | 64             |
| 7      | 80             | 128            |
| 8      | 100            | 256            |
| 9      | 200            | 512            |
| 10     | 400            | 1024           |
| 11     | 800            | 2048           |
| 12     | 1000           | 4096           |
| 13     | 2000           | 8192           |
| 14     | 4000           | 16384          |
| 15     | 8000           | 32768          |
 

