
const axios = require('axios');
axios.get('https://www.apple.com/de/').then(resp => {
    // g: globale Suche (nach einem Treffer fortsetzen)
    var refs =  new RegExp('href="(http[s]?://[^"]+)"', 'g')
    var a = resp.refs;
    console.log(a.toString());
    console.log(a);
});

