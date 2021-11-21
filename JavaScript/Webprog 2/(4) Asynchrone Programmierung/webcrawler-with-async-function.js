const process = require('process');
const fs = require('fs');
const os = require('os');
const axios = require('axios');
//const async = require('async');
const hrefs = new RegExp('href="(http[s]?://[^"]+)"', 'g');
const file = process.argv[2];
const urls = process.argv.slice(3);

if (process.argv.length < 4) throw new Error('Usage: node webcrawler-with-async-package.js <filename> <url> ...<more_urls>');
if (fs.existsSync(file)) fs.rmSync(file); // delete file if it already exists

async function processURL(url) {
    console.log('Processing URL ' + url);
    // todo process url and save the data to file
    // use axios.get() with await keyword
    let response = await axios.get(url);
    let matches = [];
    response.data.match(hrefs).forEach(link => {
        if (!matches.includes(link)) matches.push(link);
    });
    let data = 'Hyperlinks found at URL ' + url + os.EOL + matches.map(url => '  ' + url).join(os.EOL) + os.EOL;
    fs.appendFile(file, data, function (err) {
        if (err) throw new Error(err);
    });
}

const promises = urls.map(url => processURL(url));
// todo promise.all()
Promise.all(promises)
    .then( () => {
        console.log("All URLs have been processed successfully.");
    })
    .catch(err => {
        console.log("error");
    });
