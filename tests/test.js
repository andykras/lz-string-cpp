const lz = require('./lz-string-1.1.4.js')

const input = '[{"foo":42},{"pi":3.14},"long dash symbol":"—"]'
const zipped = lz.compressToBase64(input)

console.log('input: ', input)
console.log('zipped: ', zipped)

const fromCpp = 'NobwRAZg9lYFwBYBMBfANOADgS3gZgDoBGBdMAGygDsBzAAgBMBDAZwAs6WBPAWwCMo5eGEAoBGAC6QA'
console.log(zipped === fromCpp)

const unzipCpp = lz.decompressFromBase64(fromCpp)
console.log(unzipCpp)
console.log(unzipCpp === input)

// node test.js
//
// input:  [{"foo":42},{"pi":3.14},"long dash symbol":"—"]
// zipped:  NobwRAZg9lYFwBYBMBfANOADgS3gZgDoBGBdMAGygDsBzAAgBMBDAZwAs6WBPAWwCMo5eGEAoBGAC6QA
// true
// [{"foo":42},{"pi":3.14},"long dash symbol":"—"]
// true