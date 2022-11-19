const db = require('../database');

const tilitapahtumat = {
  getById: function(id, callback) {
    return db.query('select * from tilitapahtumat where idtilitapahtumat=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from tilitapahtumat', callback);
  },
  getFive: function(tilinumero, callback) {
    return db.query('select * from tilitapahtumat where tilinumero=? order by pvm DESC LIMIT 5', [tilinumero], callback);
  },
  delete: function(id, callback) {
    return db.query('delete from tilitapahtumat where idtilitapahtumat=?', [id], callback);
  },

  update: function(id, tilitapahtumat, callback) {
    return db.query(
      'update tilitapahtumat set saldo=? where idtilitapahtumat=?',
      [tilitapahtumat.saldo,id],
      callback
    );
  },
  rahanNosto: function(procedure_params, callback) {
      return db.query(
        'CALL rahanNosto (?,?)',
        [procedure_params.tili, procedure_params.summa],
        callback    
    );
  },
  getTen: function(procedure_params, callback){
    return db.query('CALL getTen (?, ?)',
    [procedure_params.tilino, procedure_params.offset_row_count], callback 
    );
  },
  // get10: function(tilinumero, offset_row_count, callback) {
  //   return db.query('select * from tilitapahtumat ORDER BY pvm WHERE tilinumero=? DESC LIMIT offset_row_count=? , 9',
  //  [tilino, offset_row_count], callback);
  // },
  rahanSiirto: function(procedure_params, callback) {
    return db.query(
      'CALL rahanSiirto (?,?,?)',
      [procedure_params.tili_saaja, procedure_params.tili_maksaja, procedure_params.summa],
      callback    
  );
}
};

module.exports = tilitapahtumat;