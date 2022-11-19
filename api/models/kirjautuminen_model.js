const db = require('../database');

const kirjautuminen={
  tarkistaPinkoodi: function(id, callback) {
      return db.query('SELECT pinkoodi FROM kortti WHERE id_kortti = ?',[id], callback); 
    }
};
          
module.exports = kirjautuminen;