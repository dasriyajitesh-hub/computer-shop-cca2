pipeline {
    agent any
    options { timestamps(); disableConcurrentBuilds() }
    environment {
        AWS_REGION = 'ap-south-1'
        AWS_ACCOUNT_ID = '906462447728'
        ECR_REPOSITORY = 'comp_rep'
        IMAGE_TAG = "${BUILD_NUMBER}"
        IMAGE_URI = "${AWS_ACCOUNT_ID}.dkr.ecr.${AWS_REGION}.amazonaws.com/${ECR_REPOSITORY}"
    }
    stages {
        stage('Checkout') {
            steps { checkout scm; sh 'echo "Checked out Computer Shop C++ source."' }
        }
        stage('Build and Test') {
            steps {
                sh '''
                    set -eu
                    docker run --rm -v "$WORKSPACE:/src" -w /src gcc:13 \\
                      bash -lc 'g++ -std=c++17 -Wall -Wextra -pedantic COMPSHOP.cpp -o compshop-test && g++ -std=c++17 -Wall -Wextra -pedantic webserver.cpp -o webserver-test && test -x compshop-test && test -x webserver-test'
                    echo "C++ compile checks passed."
                '''
            }
        }
        stage('Docker Build') {
            steps { sh 'docker build -t ${IMAGE_URI}:${IMAGE_TAG} -t ${IMAGE_URI}:latest .' }
        }
        stage('Push Image to Amazon ECR') {
            steps {
                withCredentials([[$class: 'AmazonWebServicesCredentialsBinding', credentialsId: 'aws-ecr-credentials']]) {
                    sh '''
                        set -eu
                        aws ecr get-login-password --region "$AWS_REGION" | docker login --username AWS --password-stdin "$AWS_ACCOUNT_ID.dkr.ecr.$AWS_REGION.amazonaws.com"
                        docker push "$IMAGE_URI:$IMAGE_TAG"
                        docker push "$IMAGE_URI:latest"
                        docker logout "$AWS_ACCOUNT_ID.dkr.ecr.$AWS_REGION.amazonaws.com"
                    '''
                }
            }
        }
        stage('Deploy to Minikube') {
            steps {
                withCredentials([[$class: 'AmazonWebServicesCredentialsBinding', credentialsId: 'aws-ecr-credentials']]) {
                    sh '''
                        set -eu
                        minikube status
                        kubectl create secret docker-registry ecr-registry-secret \
                          --docker-server="$AWS_ACCOUNT_ID.dkr.ecr.$AWS_REGION.amazonaws.com" \
                          --docker-username=AWS --docker-password="$(aws ecr get-login-password --region "$AWS_REGION")" \
                          --dry-run=client -o yaml | kubectl apply -f -
                        sed "s|__IMAGE__|${IMAGE_URI}:${IMAGE_TAG}|g" k8s/deployment.yaml | kubectl apply -f -
                        kubectl apply -f k8s/service.yaml
                        kubectl rollout status deployment/computer-shop --timeout=180s
                        kubectl get pods -o wide
                        kubectl get deployment,service
                    '''
                }
            }
        }
        stage('Verify Application') {
            steps {
                sh '''
                    set -eu
                    kubectl get pods -l app=computer-shop
                    kubectl get service computer-shop
                    echo "Use: minikube service computer-shop --url"
                '''
            }
        }
    }
    post {
        success { echo 'Computer Shop C++ CI/CD pipeline completed successfully.' }
        failure { echo 'Pipeline failed. Inspect the failed stage console output.' }
    }
}
