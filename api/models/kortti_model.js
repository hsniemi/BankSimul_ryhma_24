const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds=10;
const kortti={
  getAll: function(callback) {
    return db.query('select * from kortti', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from kortti where id_kortti=?', [id], callback);
  },
  getTilinumeroByKorttiId: function(id, callback){
    return db.query('select tilinumero from kortti where id_kortti=?', [id], callback);
  },
  add: function(kortti, callback) {
    bcrypt.hash(kortti.pinkoodi, saltRounds, function(err, hash) {
      return db.query('insert into kortti (pinkoodi, id_kortti, tilinumero, id_asiakas) values(?,?,?,?)',
      [hash, kortti.id_kortti, kortti.tilinumero, kortti.id_asiakas], callback);
    });
  },
  delete: function(id, callback) {
    return db.query('delete from kortti where id_kortti=?', [id], callback);
  },
  update: function(id, kortti, callback) {
    bcrypt.hash(kortti.pinkoodi, saltRounds, function(err, hash) {
      return db.query('update kortti set pinkoodi=? where id_kortti=?',
      [hash, id], callback);
    });
  },
  asiakasTiedot: function(procedure_params, callback) {
    return db.query(
      'CALL asiakkaan_tiedot_by_id_kortti(?)',
      [procedure_params.korttiID],callback
    );
    }
};
          
module.exports = kortti;