

const upload = multer({ dest: 'uploads_tmp/' });
const app = express();
app.use(require('cors')());
app.use(express.json());


if(!fs.existsSync('uploads')) fs.mkdirSync('uploads');
if(!fs.existsSync('uploads_tmp')) fs.mkdirSync('uploads_tmp');


let s3;
if(USE_S3){
s3 = new S3({
accessKeyId: process.env.S3_KEY,
secretAccessKey: process.env.S3_SECRET,
endpoint: process.env.S3_ENDPOINT || undefined,
region: process.env.S3_REGION || undefined,
s3ForcePathStyle: !!process.env.S3_ENDPOINT,
});
}


app.post('/upload', upload.array('files'), async (req, res)=>{
try{
const out = [];
for(const file of req.files){
const name = file.originalname;
if(USE_S3){
const body = fs.createReadStream(file.path);
await s3.upload({ Bucket: process.env.S3_BUCKET, Key: name, Body: body }).promise();
fs.unlinkSync(file.path);
} else {
const dest = path.join('uploads', name);
fs.renameSync(file.path, dest);
}
out.push({ name, size: file.size });
}
res.json({ ok:true, files: out });
}catch(e){ console.error(e); res.status(500).json({error: e.message}); }
});


app.get('/files', async (req, res)=>{
if(USE_S3){
const list = await s3.listObjectsV2({ Bucket: process.env.S3_BUCKET }).promise();
const files = (list.Contents||[]).map(o=>({ id:o.Key, name:o.Key, size:o.Size }));
return res.json(files);
}
const files = fs.readdirSync('uploads').map(name => {
const stat = fs.statSync(path.join('uploads', name));
return { id:name, name, size: stat.size };
});
res.json(files);
});


app.get('/files/:name', async (req, res)=>{
const name = req.params.name;
if(USE_S3){
const stream = s3.getObject({ Bucket: process.env.S3_BUCKET, Key: name }).createReadStream();
res.setHeader('Content-Disposition', `attachment; filename="${name}"`);
stream.pipe(res);
stream.on('error', err => res.status(500).end(err.message));
return;
}
const p = path.join('uploads', name);
if(!fs.existsSync(p)) return res.status(404).send('Not found');
res.download(p, name);
});


app.listen(PORT, ()=> console.log('Server running on', PORT));