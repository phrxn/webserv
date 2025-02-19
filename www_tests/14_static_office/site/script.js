// Function to track the downloads
const downloadLinks = document.querySelectorAll('a[download]');

downloadLinks.forEach(link => {
    link.addEventListener('click', function(event) {

        const fileName = event.target.getAttribute('download') || event.target.textContent.trim();
        
        alert(`The file "${fileName}" is being downloaded.`);
        console.log(`The file ${fileName} is being downloaded.`);
    });
});
